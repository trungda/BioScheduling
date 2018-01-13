#!/bin/bash

echo "Filename? \c"
read filename
input="test/$filename.ip"
#echo $input

echo "Mixers? \c"
read nm
echo "Reservoirs? \c"
read nr

echo "TimeStepSize? \c"
read t

cd test/
g++ arch_gen.cpp -o arch_gen
./arch_gen << EOF
$nm $nr $t
EOF
cd ../

make bin/parser
./bin/parser < $input

cd src/cplex
foo="../../build/$filename.o"
make FOO=$foo

../../bin/run

make clean
cd ../../
make clean
rm test/arch_gen
