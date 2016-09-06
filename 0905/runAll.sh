#!/bin/bash
filename='root_file.txt'
exec< $filename

while read line
do
    #python MonoHBranchReader.py -i
    
    #echo "MonoH-"
    echo "$line"
    test=${line%%/crab*}
    test2=${test##*MonoH-}
    #python MonoHBranchReader.py -i "$line" -a >& "$test2"combine.txt
done
