# Да се напише SHELL скрипта која ги листа сите датотеки од тековниот директориум. Потоа, зема две по 
# две датотеки од листата датотеки и ги праќа  како влезни аргументи на повикот на PERL скриптата од 
# задача 1. Резултатот од секој повик на PERL Скриптата се запишува во датотека креирана од спој на 
# имињата на двете датотеки кои се праќаат на PERL Скриптата, притоа се запишува во продолжение 
# (append).

file=$(cat ls -a | grep '^\.*$')
#file=$(find . -maxdepth 1 -type f)

file_array=($file) # niza od files
num_files=${#file_array[@]} #number of files in the array

for((i=0;i<$num_files;i+=2));do
    if [ $((i+1)) -lt $num_files ];then
        file1=${file_array[$i]}
        file2=${file_array[$(i+1)]}

        demo_file="${file1}_${file2}_output.txt"
        execute=$(Python prva.py "$file1" "$file2")
        echo "$execute" >> "$demo_file"

        echo "Processes files "$file1" and "$file2" are appended into $demo_file"
    fi
done

