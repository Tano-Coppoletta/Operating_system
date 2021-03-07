#!/usr/bin/bash

if [ $# -eq 0 ]
then
	echo scrivere nome file:
	read file;
else
	file = $1;
fi

i=0;
last=0;
for word in $(cat $file)
do
		for inserita in ${vett[*]}
		do
			if [ "$inserita" = "$word" ]
			then 
				i=1;
				
			fi
		done

		if [ "$i" -eq 0 ]
		then
			occorrenze=$(grep $word $file -c -w);
			echo $word $occorrenze;
			vett[$last]="$word";
			let last=last+1;
		fi
		i=0;

done
