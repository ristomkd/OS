#Да се напише SHELL скрипта која како аргумент од командна линија добива име на влезна
#датотека. Доколку не се прати аргумент на командна линија, тогаш се пребарува датотека со име
#„naredbi.txt“ во тековниот директориум и неговите поддиректориуми и доколку се најде, тогаш се
#копира таа датотека во тековниот директориум (доколку истата не е во тековниот директориум).
#Доколку се најде датотеката, тогаш се печати нејзината содржина на екран, инаку се печати
#порака дека датотеката не е пронајдена.

#!/bin/bash

if [ $? -eq 1 ];then #dali e praten argument
    vlez="$1" #go vnesuvame vo vlez
else 
    echo "Ne vnesovte dovolno argumenti"
    for file in $(find . -type f -name "naredbi.txt");do 
    
    vlez="$file" # /home/user/documents/naredbi.txt
    break
    done
fi


if [ -n "$vlez" ];then #dali ne e prazna niza
    base_name=$(basename "$vlez") #naredbi.txt go trga /home/.. (path)
    if [ ! -f "$base_name" ];then #dali ne postoi vo segashniot direktorium
        cp "$vlez" "$base_name" #go kopira $vlez "naredbi.txt" vo tekovniot 
        echo "File '$base_name' copied to current directory"
    fi
    
    echo "File found"
    cat "$base_name"
else 
    echo "file 'naredbi.txt' hasn't been found"
    exit 1
fi

# slicna zadaca, samo sto go smestuva file-ot vo backup directory

if [ -n "$input_file" ]; then
    base_name=$(basename "$input_file")
    if [ -s "$input_file" ]; then #dali postoi I ne e prazna niza 
        backup_dir="backup" #imeto  na backup direktoriumot
        if [ ! -d "$backup_dir" ]; then # dokolku ne postoi direktorium so vakvo ime
            mkdir "$backup_dir" 
        fi
        mv "$input_file" "$backup_dir/$base_name"
        echo "File '$base_name' moved to backup directory"
    else
        echo "File '$input_file' is empty or does not exist"
    fi
fi
