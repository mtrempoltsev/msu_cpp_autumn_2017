#!/bin/bash

echo Valid tests
./result "2+2" = 4 --- exit code is 0
./result "2+ 2" = 4 --- exit code is 0
./result "2 +2" = 4 --- exit code is 0
./result "2 + 2" = 4 --- exit code is 0
./result "2 +   2" = 4 --- exit code is 0
./result "2" = 2 --- exit code is 0
./result "-2" = -2 --- exit code is 0
./result "-2 - 2" = -4 --- exit code is 0
./result "2 -2" = 0 --- exit code is 0
./result "2 - -2" = 4 --- exit code is 0
./result "100 + 1" = 101 --- exit code is 0
./result "101 + 1" = 102 --- exit code is 0
./result "8 - 6 * 2 / 2" = 2 --- exit code is 0
./result "8 - 6 / 2 * 2" = 2 --- exit code is 0
./result "8 - 6 / 2 * -2" = 14 --- exit code is 0
./result "2 + 3 * 4 - -2" = 16 --- exit code is 0
echo Invalid tests
./result "2 / 0" = --- exit code is 136
./result "2 -+ 2" = 0 --- exit code is 0
./result "2 ++ 2" = 4 --- exit code is 0
./result "2 c 2" = error in input! --- exit code is 0
./result "1.5 + 1.5" = error in input! --- exit code is 0
