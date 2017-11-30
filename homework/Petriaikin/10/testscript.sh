#!/bin/bash

./PingPong | sed 's/ping pong //g' | wc -c

if [ $? = "0" ]
then
	echo "Threading test OK"
else
	echo "Failed threading test"
fi

