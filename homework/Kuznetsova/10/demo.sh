#!/bin/bash
make clean
make
echo "running ./ping_pong for 3 seconds"
timeout 3s ./ping_pong 
make clean
