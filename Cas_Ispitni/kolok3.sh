#!/bin/bash

for dat in $@ #argument po argument od command line
do 
l=`find .-name $dat`

if [ .n "$l" ]
then 
    z=`sed 'p/[0-9][0-9]-[0-9][0-9]-[0-9][0-9][0-9][0-9]/' $l | wc -l`
    if [ $z -gte 1 ]
    then
        z=`python3 prva.py3 $l | wc -l`
        echo "$l $z"
    fi
fi
done