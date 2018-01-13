editor: Daiki Kitagawa
Next generation computing lab. @Ritsumeikan university
Date: March 20th 2017

Article: Contamination-Aware routing method for Sample Preparation Applications on DMFB(unpublished)

1: This folder is consists of following 4 folders/programs.
---------------------------
01_Network_flow
02_Scheduler
03a_BioRouting
03b_negotiation_based
---------------------------

folder 01 and 02 are for creating input files(DAG and Scheduled result) for 03a and 03b.
03*s are the main routing programs which 03a uses ILP and 03b uses heuristic alogrithm.
(read my article and readme file inside for more detailed information)

2: Excecuting programs

these programs can be worked like following

      input file(desired precition level and target droplets) ->

      -> 01_Network_flow(program, ilp) -> output file(will be used in next program) ->

      -> 02_Scheduler(program) -> 2 output files(DAG + scheduled result) ->

      --------> 03a_BioRouting(ilp approach) -> Routing result
	  |
	  ----> 03b_negotiation_based(heuristic approach) -> Routing result
