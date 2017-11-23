#!/bin/bash

mkdir Tests
tar -xzvf tests.tar.gz -C ./Tests

for name in $(find Tests -name "*.in")
do
	base_name=$(echo $name | awk '{split($0,a,"."); print a[1]}')

	./FrequencyAnalyzer "$name" "$base_name.out"
	cmp "$base_name.chk" "$base_name.out"
	
	if [ $? = "0" ]
	then
		echo "Test $name passed ok"
	else
		echo "Failed: $name"
	fi
done
