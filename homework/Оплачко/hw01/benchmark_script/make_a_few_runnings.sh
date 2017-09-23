#!/bin/bash
for ((i = 1; i <= $2; i++)); do
	echo "=====Launch #$i====="
	./$1
done;
