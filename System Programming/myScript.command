#!/bin/bash
echo Welcome to shell scripting.
myfirstvar=hello
echo $myfirstvar
myfirstvar="$myfirstvar there"
echo $myfirstvar
myfirstvar='$myfirstvar there'
echo $myfirstvar
echo Today is ‘date‘
echo Today is ’‘date‘’

echo The program name is: $0
echo "The program name is: $0"
echo 'The program name is: $0'

echo The first argument is: $1
echo The fourth argument is: $
echo All the arguments are: $*
echo The total number of argument is $#

echo Today is `date +%A%B%d%Y`