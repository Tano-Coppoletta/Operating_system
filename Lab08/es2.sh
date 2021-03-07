#!/usr/bin/bash

max=0;

if [ $# -eq 0 ];
	then
		echo scrivere nome file;
		read file
	for row in $(cat $file);
	do
		if [ $max -lt $(echo $row|wc -c) ]
		then
			max=$(echo $row|wc -c);
		fi
	done

	echo -n "num lines: $(more $file|wc -l) longest row: $max";
else
	for row in $(cat $1);
	do
		if [ $max -lt $(echo $row|wc -c) ]
		then
			max=$(echo $row|wc -c);
		fi
	done
	echo -n "num lines: $(more $1|wc -l) longest row: $max";
fi
	
