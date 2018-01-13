#include<iostream>
#include<string>
#include<string.h>
#include<cstring>
#include<cstdio>
#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<vector>
#include<math.h>

using namespace std;

class NODE
{
public:
  int id;
  float con;
  int start_time;
  int end_time;
  int module_num;
  string operation_type;
  pair<int,int> childs;
  pair<int,int> parents;

};

vector<NODE*> node_list;
vector<NODE*> storage_list;

#define STR_NUM 2
string filename;
int precision_level;
int mod_num;
int input();
int output();
int create_file();

int left_edge();
int is_exec(vector<NODE*>,NODE*);
//int is_ok_to_insert(NODE*,int);
int storage_establishment();
int is_storage(NODE*,int);
int tekitou_binder();


int main(){

  cout<<"Enter dag"<<endl;
  cin>>filename;
  cout<<"Enter # of mods to begin with"<<endl;
  cin>>mod_num;

  int err = 1;

  while(err==1){

    input();

    left_edge();
    
    storage_establishment();
  
    err=tekitou_binder();

    output();
    
    if(err==1){
      cout<<mod_num<<" modules are not enough, redo!"<<endl;
      mod_num++;
      node_list.clear();
      storage_list.clear();
    }


  }


  create_file();

  cout<<mod_num<<" modules are required"<<endl;

  return 0;
 
}

int create_file(){

  string fout = "./dag/" + filename + "_DAG";
  ofstream ofs(fout.c_str());
  
  ofs<<"#ID Operation"<<endl;
  int ix = 1;

  for(int i=0;i<node_list.size();i++){
    if(node_list[i]->parents.first == -1 && node_list[i]->parents.second == -1){
      ofs<<"I"<<ix<<" INPUT:1"<<endl;
      ix++;
      ofs<<"I"<<ix<<" INPUT:1"<<endl;
      ofs<<"O"<<node_list[i]->id<<" MIX (I"<<ix-1<<", I"<<ix<<") ";
      ix++;
    }else if(node_list[i]->parents.first == -1 || node_list[i]->parents.second == -1){
      ofs<<"I"<<ix<<" INPUT:1"<<endl;
      ix++;
      ofs<<"O"<<node_list[i]->id<<" MIX (O";
      if(node_list[i]->parents.first!=-1){
	ofs<<node_list[i]->parents.first;
      }else{
	ofs<<node_list[i]->parents.second;
      }
      ofs<<", I"<<ix-1<<") ";
    }else{
      ofs<<"O"<<node_list[i]->id<<" MIX (O"<<node_list[i]->parents.first<<", O"<<node_list[i]->parents.second<<") ";
    }

    ofs<<"(";
    if(node_list[i]->childs.first > 0){
      ofs<<"O"<<node_list[i]->childs.first<<":1, ";
    }else{
      ofs<<"T:1, ";
    }

    if(node_list[i]->childs.second > 0){
      ofs<<"O"<<node_list[i]->childs.second<<":1)";
    }else if(node_list[i]->childs.second == -1){
      ofs<<"T:1)";
    }else{
      ofs<<"W:1)";
    }
      
    ofs<<endl;

  }

  ofs<<"T OUTPUT"<<endl;
  ofs<<"W OUTPUT"<<endl;
  ofs<<"#end"<<endl;

  //scheduling result

  fout = "./dag/" + filename + "_sched";
  ofstream of2(fout.c_str());
  
  of2 << "Status: Optimal" << endl;
  of2<<"SCHEDULING RESULTS"<<endl;
  for(int i=0;i<node_list.size();i++){
    of2<<"O"<<node_list[i]->id<<" "<<node_list[i]->start_time<<" "<<endl;
  }

  of2<<"#"<<endl;
  of2<<"MIXING BINDING RESULTS"<<endl;

  vector<NODE*> m_oplist;

  for(int i=0;i<mod_num;i++){
    of2<<"Module-"<<i;

    //gather node with same mod

    for(int j=0;j<node_list.size();j++){
      if(node_list[j]->module_num == i){
	m_oplist.push_back(node_list[j]);
      }
    }

    //write in chronological order
    
    int written=0;
    int cur_t=0;

    while(written != m_oplist.size()){

      for(int j=0;j<m_oplist.size();j++){
	if(m_oplist[j]->start_time == cur_t){
	  of2<<" O"<<m_oplist[j]->id<<" ";
	  written++;
	  break;
	}
      }

      cur_t+=3;

    }

    of2<<" "<<endl;
    m_oplist.clear();

  }

  m_oplist.clear();
  of2<<"#"<<endl;
  of2<<"STORAGE BINDING RESULTS"<<endl;

  for(int i=0;i<mod_num;i++){

    of2<<"Module-"<<i;

    for(int j=0;j<storage_list.size();j++){
      if(storage_list[j]->module_num == i){
	m_oplist.push_back(storage_list[j]);
      }
    }

    int last=0;
    int cur_t=0;
    
    for(int j=0;j<m_oplist.size();j++){
      if(last < m_oplist[j]->end_time)last = m_oplist[j]->end_time;
    }


    while(cur_t < last){
      
      for(int j=0;j<m_oplist.size();j++){
	if(m_oplist[j]->start_time <= cur_t && cur_t <=m_oplist[j]->end_time){
	  of2<<" (O"<<m_oplist[j]->parents.first<<"-O"<<m_oplist[j]->childs.first<<"):"<<cur_t<<" ";
	}
      }
    
      cur_t++;
    
    }

    of2<<" "<<endl;
    m_oplist.clear();

  }

  of2<<"#";

  return 0;

}


int storage_establishment(){

  for(int i=0;i<node_list.size();i++){
    
    if(node_list[i]->childs.first > 0){
      is_storage(node_list[i],1);
    }
    
    if(node_list[i]->childs.second > 0){
      is_storage(node_list[i],2);
    }
    
  }
  
  return 0;
  
}

int is_storage(NODE *parent,int a){

  NODE *str_in;
  NODE *child;

  if(a==1){
    for(int i=0;i<node_list.size();i++){
      if(parent->childs.first == node_list[i]->id)child = node_list[i];
    }
  }else{
    for(int i=0;i<node_list.size();i++){
      if(parent->childs.second == node_list[i]->id)child = node_list[i];
    }
  }

  int gap = child->start_time - parent->end_time;

  if(gap>1){
    cout<<"Storage exist between "<<parent->id<<" and "<<child->id<<endl;
    str_in = new NODE;
    str_in->operation_type = "STORAGE";
    str_in->start_time = parent->end_time + 1;
    str_in->end_time = child->start_time - 1;
    str_in->parents.first = parent->id;
    str_in->childs.first = child->id;

    storage_list.push_back(str_in);
    
  }else if(gap<1){
    cout<<"ERROR something is wrong between "<<parent->id<<" and "<<child->id<<endl;
    return 1;
  }

  return 0;

}


int tekitou_binder(){

  int binded=0;
  int cur_t = 0;
  int module_id=0;

  int max_t=0;
  for(int i=0;i<node_list.size();i++){
    if(node_list[i]->start_time > max_t)max_t = node_list[i]->start_time;
  }

  while(cur_t<=max_t){
    for(int i=0;i<node_list.size();i++){
      if(node_list[i]->start_time == cur_t){
	node_list[i]->module_num = module_id;
	module_id++;
	binded++;
      }
    }

    int counter=1;

    for(int i=0;i<storage_list.size();i++){
      if(storage_list[i]->start_time <= cur_t && cur_t <= storage_list[i]->end_time){
	storage_list[i]->module_num = module_id;
	if(counter==1){
	  module_id++;
	  counter = 0;
	}else{
	  counter = 1;
	}
	binded++;
      }
    }

    if(module_id>mod_num){
      cout<<"ERROR!!! too many ops @ time: "<<cur_t<<endl;
      return 1;
    }


    module_id=0;
    cur_t += 3;

  }


  return 0;

}

int left_edge(){
  
  vector<NODE*> executed;
  vector<NODE*> tmp;
  vector<NODE*> candidates = node_list;
  int cur_t=0;
  int mod_left=mod_num;
  int live_droplets=0;
  
  while(executed.size() != node_list.size()){

    for(int i=0;i<candidates.size();i++){
      if(is_exec(executed,candidates[i])==0){
	tmp.push_back(candidates[i]);
      }
    }

    if(executed.size()==0){
      for(int j=0;j<tmp.size() && j<mod_num;j++){
	cout<<"inserting "<<tmp[j]->id<<endl;
	tmp[j]->start_time = cur_t;
	tmp[j]->end_time = cur_t+2;
	executed.push_back(tmp[j]);
      }
    }else{
      for(int j=tmp.size()-1;j>=0 && mod_left>0 && live_droplets <= 7;j--){
	cout<<"inserting "<<tmp[j]->id<<endl;
	tmp[j]->start_time = cur_t;
	tmp[j]->end_time = cur_t+2;
	executed.push_back(tmp[j]);
	mod_left--;
	if(tmp[j]->childs.first>0)live_droplets++;
	if(tmp[j]->childs.second>0)live_droplets++;
      }
    }

    cout<<"no more operation is executable @ time: "<<cur_t<<endl;

    live_droplets=0;
    tmp.clear();
    cur_t+=3;
    mod_left = mod_num;

  }

  return 0;

}

int is_exec(vector<NODE*> executed, NODE *candidate){

  //already executed?
  for(int i=0;i<executed.size();i++){
    if(executed[i]->id == candidate->id)return 1;
  }

  //is parent1 executed?
  int p=0;
  if(candidate->parents.first != -1){
    for(int i=0;i<executed.size();i++){
      if(executed[i]->id==candidate->parents.first){
	p=1;//already executed
	break;
      }
    }
    if(p==0)return 1; //not executed
  }

  //is parent2 executed?
  p=0;
  if(candidate->parents.second != -1){
    for(int i=0;i<executed.size();i++){
      if(executed[i]->id==candidate->parents.second){
	p=1;//already executed
	break;
      }
    }
    if(p==0)return 1; //not executed
  }


  return 0; //candidate is executable

}

int input(){


  ifstream ifs;
  ifs.open(filename.c_str());

  if(ifs.fail()){
    cerr << "error reading scheduled file" <<endl;
    return EXIT_FAILURE;
  }


  stringstream ss;
  string exp;
  NODE *node_in;

  getline(ifs,exp);
  ss.str(exp);
  
  ss>>precision_level;
  
  ss.clear();

  while(getline(ifs,exp)){
    ss.str(exp);

    int arg[6]={0};
    node_in = new NODE;
  
    int i=0;
    while(!ss.eof()){
      ss>>arg[i];
      i++;
    }

    node_in->id = arg[0];
    node_in->con = (float)arg[1] / pow(2,precision_level);
    node_in->parents.first = arg[2];
    node_in->parents.second = arg[3];
    node_in->childs.first = arg[4];
    node_in->childs.second = arg[5];
    node_in->operation_type = "MIX";

    node_list.push_back(node_in);

    ss.clear();
    
  }





  return 0;

}

int output(){

  for(int i=0;i<node_list.size();i++){
    cout<<"Id= "<<node_list[i]->id;
    cout<<" con= "<<node_list[i]->con;
    cout<<" parent1= "<<node_list[i]->parents.first;
    cout<<" parent2= "<<node_list[i]->parents.second;
    cout<<" child1= "<<node_list[i]->childs.first;
    cout<<" child2= "<<node_list[i]->childs.second;
    cout<<endl;
    cout<<" start_time= "<<node_list[i]->start_time;
    cout<<" end_time= "<<node_list[i]->end_time;
    cout<<" module num= "<<node_list[i]->module_num;
    cout<<endl;
    cout<<endl;
  }

  cout<<endl;
  cout<<"STORAGE"<<endl;
  cout<<endl;

  for(int i=0;i<storage_list.size();i++){
    cout<<"(O"<<storage_list[i]->parents.first<<"-O"<<storage_list[i]->childs.first<<"):";
    cout<<storage_list[i]->start_time<<" - "<<storage_list[i]->end_time<<endl;
    cout<<endl;
  }

  return 0;


}
