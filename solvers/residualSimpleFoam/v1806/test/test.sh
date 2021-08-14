#!/bin/bash
. $WM_PROJECT_DIR/bin/tools/RunFunctions

editer="less"

org="pitzDaily"
result="../../result"
if [ ! -d $result ]; then mkdir $result; fi

n=1
while [ true ]; do
	new=$result/${org}_${n}
	if [ ! -e $new ]; then
		cp -r $org $new
		cd $new
		start_time=`date +%s`
		./Allrun
		end_time=`date +%s`
		SS=`expr ${end_time} - ${start_time}`
		echo "Calculated in ${SS}s"
		read -p "Enter log or view: " input
		if [ "$input" = "log" ];
		then $editer log.$(getApplication)
		elif [ "$input" = "view" ]; then paraFoam; fi
		break
	fi
	n=$(( $n + 1 ))
done
