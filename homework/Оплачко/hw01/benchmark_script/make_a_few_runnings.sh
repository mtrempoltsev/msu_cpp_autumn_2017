#!/bin/bash
SOURCENAME=$1
NAME=$(basename $SOURCENAME .cpp)
g++ -std=c++11 -O2 -o $NAME ../$SOURCENAME
echo -n > ../reporting_results/$NAME\_benchmark.txt
for i in {1..5}; do
	echo "=====Launch #$i=====" >> ../reporting_results/$NAME\_benchmark.txt
	./$NAME >> ../reporting_results/$NAME\_benchmark.txt
done;
rm ./$NAME
