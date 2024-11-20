`# Да се напише SHELL скрипта која ги листа сите датотеки од тековниот директориум. Потоа, имињата
 на оние датотеки кои што имаат помалку од 1000 зборови ги праќа како аргументи од командна линија
 на повик од PERL скриптата (сите имиња ги праќа во еден повик). За оние датотеки кои што имаат
 повеќе од 1000 зборови, креира посебен повик и нивните имиња ги праќа како еден аргумент од
 командна линија.`

 file=$(ls -a | grep '^\.*$')

 file_array=($file)
 num_files=${#file_array[@]} 
 word_count=0
 small_files=()
 large_files=()
 
 `# for files in $file;do
    word_count=$(wc -w < "$file") `
 
 for((int i=0;i<num_files;i++));do
    file_word_count=$(wc -w < "${file_array[i]}")
    word_count=$((word_count + file_word_count))

    if [ "$word_count" -lt 1000 ];then
        small_files+=("${file_array[i]}")
    else
        large_files+=("${file_array[i]}")
    else
    fi
done

if [ ${#small_files[@]} -gt 0 ];then  
    small_files_list = $(echo "${small_files[@]}") #gi smestuva u single string
    execute=$(Python "py.py" "$small_files_list")
fi

for file in "${large_files[@]}";do
    execute=$(Python "py.py" "$file")
done

echo "Total word count across all files: $word_count"