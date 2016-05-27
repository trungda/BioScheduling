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
# 
#
#------------------------------------------------------------

BUILDDIR := ../../build/
OBJECTS := Functions.o 
OBJECTS_ := $(addprefix $(BUILDDIR), $(OBJECTS))
EXEC := ../../bin/run
FOO := 
# FOO := Command-line-input that specfies which program to compile

# ------------------------------------------------------------
# The programs
#-------------------------------------------------------------

$(EXEC): $(FOO) $(OBJECTS_) 
	mkdir -p ../../bin
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o $@ $^ $(CCLNFLAGS) 2>err.txt 

$(BUILDDIR)%.o: %.cpp
	mkdir -p $(BUILDDIR)
	$(CCC) -c $(CCFLAGS) $< -o $@ 

$(BUILDDIR)%.o: ../codegen/%.cpp
	mkdir -p $(BUILDDIR)
	$(CCC) -c $(CCFLAGS) $< -o $@

# ------------------------------------------------------------

clean :
	/bin/rm -rf err.txt
	/bin/rm -rf *.o *~ *.class
	/bin/rm -rf *.mps *.ord *.sos *.lp *.sav *.net *.msg *.log *.clp
	/bin/rm $(EXEC) $(FOO) $(OBJECTS_)

# ------------------------------------------------------------

# Local Variables:
# mode: makefile
# End:
