#!/usr/bin/bash

if [ $# -ne 2 ]
then
	echo errore parametri;
	exit 1;
fi

zombie=0;

while [ 1 ]
do
	line=$(ps -el|grep $1);

	if [ $? -eq 0 ]
	then
		pid=$(echo $line|cut -d ' ' -f 4);
		
		state=$(echo $line|cut -d ' ' -f 2);

		if [ "$state" = "Z" ]
		then 
			let zombie=zombie+1;
		else
			zombie=0;
			echo $pid non è zombie
		fi

		if [ $zombie -ge 5 ]
		then 
			kill -9 $pid;
			echo process $pid killed
			exit 0;
		fi
	fi
	sleep $2;

done
