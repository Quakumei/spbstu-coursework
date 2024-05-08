#!/bin/bash
script_name=$1
folder_name="$script_name.test.out.d"
mkdir $folder_name
flags=('-O2 -march=native -funroll-loops -fprofile-generate=aboba.gcda' '-O2 -march=native -funroll-loops -fprofile-use=aboba.gcda') 
for i in ${!flags[@]};
do 
    echo "Compiling $script_name with ${flags[$i]}..."
    compiled_name="$folder_name/$i-$script_name.out"
    gcc ${flags[$i]} $script_name -o "$compiled_name" && echo -e "Successful!\nSize:" && du "$compiled_name" && echo -e "Running time:" && time "$compiled_name" 
    echo 
done
