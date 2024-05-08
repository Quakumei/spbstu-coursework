#!/bin/bash
script_name=$1
flags=('-O2 -march=native -funroll-loops -flto -fipa-sra -fipa-pta -fipa-cp -fipa-cp-clone -fipa-bit-cp' '-O2 -march=native -funroll-loops -fprofile-use' '-O2 -march=native -funroll-loops -fprofile-generate') 
folder_name="$script_name.test.out.d"
mkdir $folder_name
for i in ${!flags[@]};
do 
    echo "Compiling $script_name with ${flags[$i]}..."
    compiled_name="$folder_name/$i-$script_name.out"
    gcc ${flags[$i]} $script_name -o "$compiled_name" && echo -e "Successful!\nSize:" && du "$compiled_name" && echo -e "Running time:" && time "$compiled_name" 
    echo 
done
