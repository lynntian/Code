#!/bin/bash

DATE=$(date +%F)

read -p "Please enter a file extension: " EXTENSION
read -p "Please enter a file prefix: (Press enter for $DATE)." PREFIX

if [[ -n "$PREFIX" ]]
	then
		echo $PREFIX
		DATE=$PREFIX
fi

for F in *.$EXTENSION; do
	echo "Renameing $F to ${DATE}-${F}"
	mv "$F" "${DATE}-${F}"
done