created by: Daiki Kitagawa
reffered article: A Network-Flow-Based Optimal Sample Preparation Algorithm for Digital Microfluidic Biochips(Author: Trung Anh Dinh, 2014@ASP-DAC)

1: input file

   format: simple text file
   ----EXAMPLE----
   3		<= precision level
   3 2		<= target concentration + # of droplet required(this time it offers two 3/8 droplets)
   5 1		<= same as above
   ---------------

2: compile/execution
   
   hit make to compile and execute the program
   follow the program discription afterwards, it offers some input

   in the program you will be asked following info in following order
   1. source cost
      waste cost is set to 1(fixed), if you want source and waste costs are same, type 1, otherwize type 2 or above. (see the article for more detail)
   2. input file name
      type input file name

3: output file

   the result always stored in out/ folder 
   the file name will be [inputted file name] + "_out"

   format: text file
   ----EXAMPLE----
   3			<= precision level
   1 4 -1 -1 2 3	<= #id concentration 1st_parent_id(-1 && first parent == buffer) 2nd_parent_id(-1 && second parent == source) child_id1(-1 == target) child_id2(-1 == target)
   2 2 -1 1 3 4		<= same as above
   3 3 2 1 -1 -1  	<= same as above
   4 5 2 -1 -1		<= same as above
   --------------

   this output file will be used in next program(02_scheduler)


