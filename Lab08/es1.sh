#!/usr/bin/bash

if [ $# -eq 0 ]
then
	exit 1;
fi

if [ ! -d $1 ];
then
	echo "$d is not a directory"
	exit 2;
fi

for file in $(find $1 -type f)
do
	egrep -n "$2[ \t]*\(.*\)" $file> .temp_$$;
	while read line
	do
		num_line=$(echo $line|tr : " "|cut -d " " -f 1);
		row=$(echo $line|tr : " "|cut -d " " -f 1 --complement);
		name=$(basename $file);
		echo "NUM: $num_line	 FILE: $name 	row: $row";
	done < .temp_$$ >> es1.out
	rm .temp_$$


done

sort -k 4,4 -k 2,2n es1.out > es1sort.out;
