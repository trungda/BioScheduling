created by: Daiki Kitagawa
reffered article: none

Program description: very weak scheduler
schedules multi-target dag

1: required input file

   this program requires dag file from 01_Nework program

2: excecution

   you will be asked to input following
   - input file name
   - # of modules to start with(explains later)

3: algorithm

   this program uses simple list scheduling(schedules from top to bottom in numerical order)
   since the dag file includes operation with multiple output, sometimes program finds out that the chip doesn't have enough module(unless you are using list scheduling method)
   in such case, program will abort from current scheduling process then reexcecutes the scheduling with more modules.
   (this is why the program asks # of modules)
   # of required modules will be shown in the result

4: output

   this program outputs following two files in dag/ folder

   - [inputted filename] + "_DAG"     <= redesigned dag file
   - [inputted filename] + "_sched"   <= scheduling and binding result

   description of each file is written in each file

5: when fixing this program

   if you want different scheduling method, replace left_edge() function
   when fixing a binder, try replacing tekitou_binder() function

