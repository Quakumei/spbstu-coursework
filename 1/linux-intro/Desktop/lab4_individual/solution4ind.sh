#!/bin/bash
N=$1
if [ $# -ne 1 ]
then
    echo "error: expected single argument ($# were given)"
    exit 1
fi
if [ $(bc<<<"($N)%2") -ne 1 ]
then
	echo "error: N must be uneven. ($N recieved)"
    exit 1
fi
i=$(bc<<<"($N-1)")
stars="*"
delim=" "
add=$stars$delim

# echo i=$i start=$start delim=$delim add=$add N=$N

for j in `seq 0 1 $i`
do
    for k in `seq 0 $(bc<<<"$i-$j-1")`
    do 
        echo -n "$delim"
    done
    echo -ne "$stars"
    echo
    stars="$add$stars" 
done
