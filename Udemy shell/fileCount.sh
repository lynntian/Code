#!/bin/bash

function file_count(){
	echo $1
	local FC=$(ls -1 $1 | wc -l) 
	echo $FC	
	
}

file_count $1
file_count $2
file_count $3