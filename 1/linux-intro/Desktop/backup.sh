#!/bin/bash
script_name=$1
flags=('-O0' '-Os' '-O1' '-O2' '-O3' '-O2 -march=native' '-O3 -march=native' '-O2 -march=native -funroll-loops' '-O3 -march=native -funroll-loops' )
folder_name="$script_name.test.out.d"
mkdir $folder_name
for i in ${!flags[@]};
do 
    echo "Compiling $script_name with ${flags[$i]}..."
    compiled_name="$folder_name/$i-$script_name.out"
    gcc ${flags[$i]} $script_name -o "$compiled_name" && echo -e "Successful!\nSize:" && du "$compiled_name" && echo -e "Running time:" && time "$compiled_name" 
    echo 
done
