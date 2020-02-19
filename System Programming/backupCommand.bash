#Eric Yeung
#104392784
#Backup script using tar

#!/bin/bash

fileName=$(date '+%a%b%d%T%Z%Y' | tr -d ':') #Sets fileName to the current date and time
#while omitting ":"

mkdir $fileName #Creates a new directory with fileName

while getopts ":t" opt; 
do
	case "${opt}" in
	t)
		alias targetDirectory="~$2" #Sets targert directory to one specified in command line

		tar cvf archive.tar *.$3 
		rm *.$3

		for i in "${@:4}" #:4 allows me to ignore the first 3 arguments
		do
		tar rvf archive.tar *.$i
		mv archive.tar $fileName
		rm *.$i
		done 
		echo "source files deleted"
		;;
	*)

		for i in "${@:2}" #passing arguments as array to iterate through it
		do
		tar rvf archive.tar *.$i
		mv archive.tar $fileName
		rm *.$i
		done
		;;
	esac
done
