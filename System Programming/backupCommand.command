*)
		typeArray=("$1")
	
		for i in ${typeArray[*]}
		do
		tar cvf archive.tar *.${typeArray[i]} 
		mv archive.tar $fileName
		rm *.${typeArray[i]}
		done
		;;