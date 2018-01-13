#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<string>
#include<string.h>
#include<sstream>
#include<math.h>

#include<ilcplex/ilocplex.h>

ILOSTLBEGIN
IloEnv env;

using namespace std;

class NODE
{
 public:
  int concentration;
  int id;
  vector<int> childs;
  vector<int> parents;
};


string filename;
int precision_level, c_source, c_buffer;
vector<pair<int,int>*> target_list;
vector<vector<int> > network_flow_node;
vector<vector<NODE*> > network_flow_edge_info;

int input();
int output();
int ILP_solve();
void create_network();

int main(){
  
  input();
  cout<<"input complete"<<endl;
  
  create_network();
  cout<<"network creation complete"<<endl;

  ILP_solve();

  output();

  return 0;

}

int ILP_solve(){


  try{

    IloModel model(env);
    
    //variables
   
    IloNumVarArray network(env);
    IloNumVar source(env,0,IloInfinity,ILOINT);
    IloNumVar buffer(env,0,IloInfinity,ILOINT);

    for(int i=0;i<precision_level;i++){
      for(int j=0;j<pow(network_flow_node[i].size(),2);j++){
	network.add(IloNumVar(env,0,IloInfinity,ILOINT));
      }
    }
    
    for(int i=0;i<network_flow_node[precision_level].size();i++){
      network.add(IloNumVar(env,0,IloInfinity,ILOINT));
    }

    for(int i=0;i<network_flow_node[precision_level].size();i++){
      network.add(IloNumVar(env,0,IloInfinity,ILOINT));
    }

    //constraints

    //horizontal relationships

    //edges between each level must have same sum as source and buffer
    int level_iterat=0;
    for(int i=0;i<precision_level;i++){
      IloExpr horizontal(env);
      for(int j=0;j<pow(network_flow_node[i].size(),2);j++){
	horizontal += network[level_iterat + j];
      }
      model.add(horizontal == source + buffer);
      level_iterat += pow(network_flow_node[i].size(),2);
    }

    //same constraint as above but this is for edges between sink and waste 
    IloExpr horizontal2(env);
    level_iterat =0;
    for(int i=0;i<precision_level;i++)level_iterat += pow(network_flow_node[i].size(),2);

    for(int i=0;i<network_flow_node[precision_level].size();i++){
      horizontal2 += network[level_iterat + (i*2)];
      horizontal2 += network[level_iterat + (i*2)+1];
    }

    model.add(horizontal2 == source + buffer);

    //1:1 diluting constraint
    int node_iterat = 0;
    for(int i=0;i<precision_level;i++){
      for(int j=0;j<network_flow_node[i].size()-1;j++){
	for(int k=1;k<network_flow_node[i].size()-j;k++){
	  int cur = node_iterat + j + k; 
	  model.add(network[cur] == network[cur + ( (network_flow_node[i].size() - 1) * k)]);
	}
	node_iterat += network_flow_node[i].size();
      }
      node_iterat += network_flow_node[i].size();
    }

    //vertical relationships

    model.add(network[0]+network[1] == buffer);
    model.add(network[2]+network[3] == source);

    for(int i=1;i<precision_level+1;i++){
      for(int j=0;j<network_flow_node[i].size();j++){
	IloExpr vertical_c(env);
	IloExpr vertical_p(env);
	for(int k=0;k<network_flow_edge_info[i][j]->childs.size();k++){
	  vertical_c += network[ network_flow_edge_info[i][j]->childs[k] ];
	}
	for(int k=0;k<network_flow_edge_info[i][j]->parents.size();k++){
	  vertical_p += network[ network_flow_edge_info[i][j]->parents[k] ];
	}
	model.add(vertical_c == vertical_p);
      }
    }

    //target constraint
    int last_level_init=0;
    int total_target_dps=0;
    for(int i=0;i<precision_level;i++)last_level_init += pow(network_flow_node[i].size(),2);

    for(int i=0;i<target_list.size();i++){
      model.add(network[last_level_init + (target_list[i]->first * 2)] == target_list[i]->second);
      total_target_dps += target_list[i]->second;
    }
    
    IloExpr sink_edge(env);
    for(int i=0;i<network_flow_node[precision_level].size();i++){
      sink_edge += network[last_level_init + (i*2)];
    }
    model.add(sink_edge == total_target_dps);

    //waste constraint

    model.add(network[last_level_init + 1] == 0);
    model.add(network[last_level_init + ((network_flow_node[precision_level].size()-1) * 2) + 1] == 0);
    
    for(int i=1;i<network_flow_node[precision_level].size()-1;i++){
      model.add(network[last_level_init + (i * 2) + 1] <= 1); 
    }

    //objective
    IloObjective obj;
    obj = IloMinimize(env, (source * c_source) + buffer);

    model.add(obj);

    cout<<"all constraints are set, executing ilp..."<<endl;

    IloCplex cplex(model);
    cplex.exportModel("model.lp");

    if(!cplex.solve()){
      env.error()<<"FAILED TO OPTIMIZE LP"<<endl;
    }

    cplex.writeSolution("sol.sol");

    IloNumArray network_ans(env);
    int source_ans;
    int buffer_ans;
    
    cplex.getValues(network_ans,network);
    source_ans = cplex.getValue(source);
    buffer_ans = cplex.getValue(buffer);

    cout<<"Source: "<<source_ans<<endl;
    cout<<"Buffer: "<<buffer_ans<<endl;

    for(int i=0;i<precision_level+1;i++){
      for(int j= 0;j<network_flow_node[i].size();j++)cout<<network_flow_node[i][j]<<" ";
      cout<<endl;

      for(int j=0;j<network_flow_node[i].size();j++){
	int flg=0;
	for(int k=0;k<network_flow_edge_info[i][j]->childs.size();k++){
	  if(network_ans[ network_flow_edge_info[i][j]->childs[k] ] != 0){
	    
	    if(flg==0){
	      cout<<"( "<<network_flow_node[i][j]<<": ";
	      flg=1;
	    }

	    if(j!=k){
	      cout<<network_ans[ network_flow_edge_info[i][j]->childs[k] ]<<"Dps->";
	      if(i!=precision_level){
		cout<<network_flow_node[i+1][j+k]<<" ";
	      }else{
		if(k==0){
		  cout<<"OUT ";
		}else{
		  cout<<"WASTE ";
		}
	      }
	    }

	  }
	}
	if(flg==1)cout<<") ";
      }
      cout<<endl;
    }

    //dag formulation

    vector<NODE*> dag;
    NODE *tmp_node;
    node_iterat = 0;
    int id_in = 0;
    for(int i=0;i<precision_level;i++){
      for(int j=0;j<network_flow_node[i].size();j++){
	for(int k=1;k<network_flow_node[i].size()-j;k++){
	  //	  int parent1 = node_iterat + j + k;
	  // int parent2 = node_iterat + j + k + ((network_flow_node[i].size() - 1) * k);
	  //int num_node = network_ans[ network_flow_edge_info[i][j]->childs[j+k] ];
	  if(round(network_ans[ network_flow_edge_info[i][j]->childs[j+k] ]) != 0){
	    //	     cout<<"creating "<<round(network_ans[ network_flow_edge_info[i][j]->childs[j+k] ])<<" of ";
	    for(int l=0;l < round(network_ans[ network_flow_edge_info[i][j]->childs[j+k] ]);l++){
	      id_in++;
	      tmp_node = new NODE;
	      tmp_node->id=id_in;
	      tmp_node->concentration=(network_flow_edge_info[i][j]->concentration + network_flow_edge_info[i][j+k]->concentration) / 2;
	     
	      //	      cout<<tmp_node->concentration<<endl;
	      // cout<<" by "<<network_flow_edge_info[i][j]->concentration<<" and "<<network_flow_edge_info[i][j+k]->concentration<<endl;

	      //1st parent node id insertion
	      if(network_flow_edge_info[i][j]->concentration == 0){
		tmp_node->parents.push_back(-1);
	      }else{
		for(int m=0;m<dag.size();m++){
		  if((dag[m]->concentration == network_flow_edge_info[i][j]->concentration) && dag[m]->childs.size() < 2){
		    dag[m]->childs.push_back(tmp_node->id);
		    tmp_node->parents.push_back(dag[m]->id);
		    break;
		  }
		  if(m==dag.size()-1){
		    cout<<"PARENT1 NOT FOUND, i= "<<i<<" j= "<<j<<" k= "<<k<<" con= "<<network_flow_edge_info[i][j]->concentration<<endl;
		    int breaker;
		    cin>>breaker;
		  }
		}
	      }
	      
	      //2nd parent node id insertion
	      if(network_flow_edge_info[i][j+k]->concentration == pow(2,precision_level)){
		tmp_node->parents.push_back(-1);
	      }else{
	
		for(int m=0;m<dag.size();m++){
		  if((dag[m]->concentration == network_flow_edge_info[i][j+k]->concentration) && dag[m]->childs.size() < 2){
		    dag[m]->childs.push_back(tmp_node->id);
		    tmp_node->parents.push_back(dag[m]->id);
		    break;
		  }
	
		  if(m==dag.size()-1){
		    cout<<"PARENT2 NOT FOUND, i= "<<i<<" j= "<<j<<" k= "<<k<<" con= "<<network_flow_edge_info[i][j]->concentration<<endl;
		    int breaker;
		    cin>>breaker;
		  }
	
		}

	      }
	      
	      dag.push_back(tmp_node);

	    }
	  }
	  
	}
	node_iterat += network_flow_node[i].size();
      }
      node_iterat += network_flow_node[i].size();
    }

    for(int i=0;i<target_list.size();i++){
      for(int j=0;j<target_list[i]->second;j++){
	for(int k=0;k<dag.size();k++){
	  if(target_list[i]->first == dag[k]->concentration && dag[k]->childs.size() < 2){
	    dag[k]->childs.push_back(-1);
	    break;
	  }
	} 
      }
    }

    for(int i=0;i<dag.size();i++){
      cout<<"Oid: "<<dag[i]->id;
      cout<<" Con: "<<dag[i]->concentration;
      if(dag[i]->parents.size()==2){
	cout<<" Parent1: "<<dag[i]->parents[0];
	cout<<" Parent2: "<<dag[i]->parents[1];
      }else{
	cout<<endl;
	cout<<"WIERD NODE FOUND, NO PARENTS"<<endl;
	cout<<"OID: "<<dag[i]->id<<" CON: "<<dag[i]->concentration<<endl;
	cout<<endl;
      }

      if(dag[i]->childs.size()==2){
	cout<<" Child: "<<dag[i]->childs[0];
	cout<<" Child2: "<<dag[i]->childs[1];
      }else if(dag[i]->childs.size()==1){
	cout<<" Child: "<<dag[i]->childs[0];
      }else{
	cout<<" Op WITH NO CHILD";
      }

      cout<<endl;
    }
 
    string fout = "./out/" + filename + "_out";
    ofstream ofs(fout.c_str());
    
    ofs << precision_level << endl;

    for(int i=0;i<dag.size();i++){
      ofs << dag[i]->id << " " << dag[i]->concentration<<" ";
      for(int j=0;j<dag[i]->parents.size();j++){
	ofs<<dag[i]->parents[j]<<" ";
      }

      for(int j=0;j<dag[i]->childs.size();j++){
	ofs<<dag[i]->childs[j];
	if(j!=dag[i]->childs.size()-1)ofs<<" ";
      }
      if(i!=dag.size()-1)ofs<<endl;
    }




  }catch(IloException& e){
    cerr << "Unknown exception caught" <<endl;
  
  }
    

  

  return 0;

}

void create_network(){

  vector<int> node_in;
  node_in.push_back(0);
  node_in.push_back(pow(2,precision_level));
  
  network_flow_node.push_back(node_in);

  for(int i=1;i<precision_level+1;i++){
    vector<int> tmp;
    for(int j=0;j<network_flow_node[i-1].size();j++){
      tmp.push_back(network_flow_node[i-1][j]);
      if(j!=network_flow_node[i-1].size()-1)tmp.push_back((network_flow_node[i-1][j] + network_flow_node[i-1][j+1])/2);
      
    }

    network_flow_node.push_back(tmp);

  }

  //establishing parents and childs

  NODE *node_tmp;
  for(int i=0;i<precision_level+1;i++){
    vector<NODE*> n_tmp_list;
    for(int j=0;j<network_flow_node[i].size();j++){
      node_tmp = new NODE;
      node_tmp->concentration = network_flow_node[i][j];
      n_tmp_list.push_back(node_tmp);
    }
    network_flow_edge_info.push_back(n_tmp_list);
  }

  int init=0;
  int cur;
  int child_c;
  for(int i=0;i<precision_level;i++){
    for(int j=0;j<network_flow_node[i].size();j++){
      for(int k=0;k<network_flow_node[i].size();k++){
	cur = init + (network_flow_node[i].size() * j) + k;
	if(k==j){
	  //searching same concentration
	  for(int l=0;l<network_flow_node[i+1].size();l++){
	    if(network_flow_edge_info[i][j]->concentration == network_flow_edge_info[i+1][l]->concentration){
	      network_flow_edge_info[i+1][l]->parents.push_back(cur);
	      network_flow_edge_info[i][j]->childs.push_back(cur);
	      break;
	    }
	  }

	}else{
	  //searching diluted concentration
	  child_c = (network_flow_edge_info[i][j]->concentration + network_flow_edge_info[i][k]->concentration) / 2;
	  for(int l=0;l<network_flow_node[i+1].size();l++){
	    if(child_c == network_flow_edge_info[i+1][l]->concentration){
	      network_flow_edge_info[i+1][l]->parents.push_back(cur);
	      network_flow_edge_info[i][j]->childs.push_back(cur);
	      break;
	    }
	  }
	}
      }
      
    }
    
    init += pow(network_flow_node[i].size(),2);

  }

  int last_level_init = 0;
  for(int i=0;i<precision_level;i++)last_level_init += pow(network_flow_node[i].size(),2);
  for(int i=0;i<network_flow_node[precision_level].size();i++){
    network_flow_edge_info[precision_level][i]->childs.push_back(last_level_init + (i*2));
    network_flow_edge_info[precision_level][i]->childs.push_back(last_level_init + (i*2) + 1);
  }

}


int input(){  c_source = 0;
  c_buffer = 1;

  while(c_source <= 0 || c_source >=3){
    cout<<"ENTER source cost"<<endl;
    cin>>c_source;
  }

  string exp;

  cout<<"Enter Target file name"<<endl;
  cin>>filename;

  ifstream ifs;
  ifs.open(filename.c_str());

  if(ifs.fail()){
    cerr<<"error reading target file"<<endl;
    return EXIT_FAILURE;
  }
  
  stringstream ss;
  pair<int,int> *tmp;

  getline(ifs,exp);

  ss.str(exp);
  ss>>precision_level;
  ss.clear();

  while(getline(ifs,exp)){
    
    ss.str(exp);

    tmp = new pair<int,int>;

    ss>>tmp->first;
    ss>>tmp->second;

    ss.clear();
    
    target_list.push_back(tmp);

  }

  return 0;

}

int output(){

  cout<<"precision level = "<<precision_level<<endl;

  for(int i=0;i<target_list.size();i++){
    
    cout<<target_list[i]->first<<" "<<target_list[i]->second<<endl;

  }

  return 0;

}
