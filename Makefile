CC := g++
CFLAGS := -g -std=c++11
SRCDIR := src/parser/
BUILDDIR := build/
SOURCES := main.cpp Node.cpp AppGraph.cpp ChipArch.cpp
OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS_ := $(addprefix $(BUILDDIR), $(OBJECTS))

bin/parser: $(OBJECTS_)
	$(CC) $(CFLAGS) $(OBJECTS_) -o $@ 2>err.txt 

$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm  $(OBJECTS_) bin/parser

.PHONY: clean