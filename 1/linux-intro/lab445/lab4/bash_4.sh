#!/bin/bash
if [ $# -lt 3 ] || [ $(bc<<<"($#-1)%2") -ne 0 ]
then
    echo "There must be at least three arguments, count is not even."
    exit 1
fi
res=$1

for i in `seq 1 $(bc<<<"($#-1)/2")`
do
    # Debug
    #echo "#######"
    #echo "$i $#"
    #echo "$1 $2 $3"
    
    if [ $(bc<<<$3) -eq 0 ] && [ "$2"="/" ]
    then
        echo "DivisionByZeroError"
        exit 1
    fi
    if [ $2 != "+" ] && [ $2 != "-" ] && [ $2 != "/" ] && [ $2 != "x" ] && [ $2 != "X" ]
    then
        echo "Unsupported operation"
        exit 1
    fi
    
    if [ $2 = "x" ] || [ $2 = "X" ]
    then
        operation="*"
    else
        operation="$2"
    fi
    
    res=`bc<<<"scale=6;$res $operation $3"`
    shift 2

    done

echo "############"
echo $res
# $1 $2 - operation $3

