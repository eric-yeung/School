#!/bin/bash

typeArray=("$@")

fileName=$(date '+%a%b%d%T%Z%Y' | tr -d ':')

mkdir $fileName

#for i in ${typeArray[*]}
#	do
#		tar cvf archive.tar *.${typeArray[i]} 
#		mv archive.tar $fileName
#		rm *.${typeArray[i]}
#	done

