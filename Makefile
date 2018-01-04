CC := g++
CFLAGS := -g -std=c++11
SRCDIR := src/parser/
BUILDDIR := build/
SOURCES := main.cpp Node.cpp AppGraph.cpp ChipArch.cpp CodeGen.cpp
OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS_ := $(addprefix $(BUILDDIR), $(OBJECTS))

bin/parser: $(OBJECTS_)
	mkdir -p bin/
	$(CC) $(CFLAGS) $(OBJECTS_) -o $@ 2>err.txt 

$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@	

$(BUILDDIR)%.o: src/codegen/%.cpp
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm  -r $(BUILDDIR) bin/
	rm err.txt

.PHONY: clean