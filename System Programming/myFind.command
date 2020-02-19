#!/bin/bash

name=$2

for (( i=0; c<=$3; i++ ))
do
	name+=?	
done

ls $1/name | wc -l