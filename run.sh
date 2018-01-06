#!/bin/sh

echo "Filename? \c"
read filename
input="test/$filename.ip"
echo $input

echo "Mixers? \c"
read nm
echo "Reservoirs? \c"
read nr

echo "TimeStepSize? \c"
read t

cd test
./test/arch_gen <<< "$nm $nr $t"
cd ..

make bin/parser
./bin/parser < $input

cd src/cplex
foo="../../build/$filename.o"
make FOO=$foo

../../bin/run

make clean
cd ../../
make clean
