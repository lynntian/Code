#!/bin/bash
echo $(ls)
#read -p "Input file or dir name: " FILENAME

for F in "$@"
do

if [[ -f $F ]]
	then
	echo "File $F is a regular file"
elif [[ -d $F ]]
	then
	echo "File $F is a DIR"
else
	echo "File $F is other type"
fi

done
