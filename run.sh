#!/bin/sh

read filename
input="test/$filename.ip"
echo $input

make bin/parser
./bin/parser < $input

cd src/cplex
foo="../../build/$filename.o"
make FOO=$foo

../../bin/run

make clean
cd ../../
make clean
