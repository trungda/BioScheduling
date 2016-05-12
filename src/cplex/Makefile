SYSTEM     = x86-64_sles10_4.1
LIBFORMAT  = static_pic

#------------------------------------------------------------
#
# When you adapt this makefile to compile your CPLEX programs
# please copy this makefile and set CPLEXDIR and CONCERTDIR to
# the directories where CPLEX and CONCERT are installed.
#
#------------------------------------------------------------

CPLEXDIR	= /home/fuko/trungda/CPLEX/cplex
CONCERTDIR 	= /home/fuko/trungda/CPLEX/concert

#---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------

CCC = g++ -O0
CC  = gcc -O0

# ---------------------------------------------------------------------
# Compiler options 
# ---------------------------------------------------------------------

CCOPT = -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD
COPT  = -m64 -fPIC -fno-strict-aliasing 
JOPT  = -classpath $(CPLEXDIR)/lib/cplex.jar -O

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXJARDIR   = $(CPLEXDIR)/lib/cplex.jar
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CCLNDIRS  = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR)
CLNDIRS   = -L$(CPLEXLIBDIR)
CCLNFLAGS = -lconcert -lilocplex -lcplex -lm -pthread
CLNFLAGS  = -lcplex -lm -pthread

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include

EXDIR         = $(CPLEXDIR)/examples
EXINC         = $(EXDIR)/include
EXSRCCPP      = $(EXDIR)/src/cpp

CFLAGS  = $(COPT)  -I$(CPLEXINCDIR)
CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) 
JCFLAGS = $(JOPT)


#------------------------------------------------------------
#  make all      : to compile the examples. 
#  make execute  : to compile and execute the examples.
#------------------------------------------------------------

CPP_EX = ilp1 

execute_cpp: $(CPP_EX)
	./ilp1.cpp	
# ------------------------------------------------------------

clean :
	/bin/rm -rf *.o *~ *.class
	/bin/rm -rf $(CPP_EX)
	/bin/rm -rf *.mps *.ord *.sos *.lp *.sav *.net *.msg *.log *.clp

# ------------------------------------------------------------
#
# The examples
#
parabolic-2: parabolic-2.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o parabolic-2 parabolic-2.o $(CCLNFLAGS)
parabolic-2.o: parabolic-2.cpp
	$(CCC) -c $(CCFLAGS) parabolic-2.cpp -o parabolic-2.o 

pcr: pcr.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o pcr pcr.o $(CCLNFLAGS)
pcr.o: PCR.cpp
	$(CCC) -c $(CCFLAGS) PCR.cpp -o pcr.o 

brad: brad.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o brad brad.o $(CCLNFLAGS)
brad.o: brad.cpp
	$(CCC) -c $(CCFLAGS) brad.cpp -o brad.o 

# Local Variables:
# mode: makefile
# End:
