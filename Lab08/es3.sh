#!/usr/bin/bash

if [ $# -eq 0 ];
then
	echo scrivere nome direttorio;
	read dir

	if [ -d $dir ];
	then
		for file in $(find $dir -type f)
		do
			file_caps=$(basename $file|tr '[a-z]' '[A-Z]');
			dirname=$(dirname $file);
			fullname=$(echo $dirname/$file_caps);
			mv $file $fullname;
		done
		for diret in $(find $dir -type d)
		do
			dir_caps=$(basename $diret|tr '[a-z]' '[A-Z]');
			dirname=$(dirname $diret);
			echo $dirname
			fullname=$(echo $dirname/$dir_caps);
			echo $fullname;
			mv $diret $fullname;
		done
	fi
fi

