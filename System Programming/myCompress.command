#!/bin/bash

myArray=("$@")

for i in ${myArray[*]}
do
	gzip *.${myArray[i]}
done