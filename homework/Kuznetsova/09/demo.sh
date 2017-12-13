#!/bin/bash
make clean
make
echo "EXAMPLE 1 ./dict "
./dict 
[ -e deleted_input.txt ] && rm deleted_input.txt
echo "-----------------"
echo "EXAMPLE 2 ./dict deleted_input.txt output.txt"
./dict deleted_input.txt output.txt
echo "-----------------"
echo "EXAMPLE 3 ./dict input.txt output.txt"
echo "input.txt"
cat input.txt
echo "---run program---"
./dict input.txt output.txt
echo "output.txt"
cat output.txt
make clean
