# Да се напише SHELL скрипта која како аргумент добива листа од имиња од датотеки. Скриптата, за
# секоја датотека (име од датотека) да провери дали ја има како датотека во тековниот директориум, или
# под-директориуми. Доколку ја има, проверува дали датотеката (во нејзината содржина) има барем еден
# валиден датум (DD-MM-YYYY), и доколку нема, ја игнорира. Доколку има валиден датум, тогаш ја
# повикува PERL скриптата и како прв аргумент го праќа името на датотеката, и т.н. со сите датотеки што
# се пратени како аргументи од командна линија. За секоја датотека што ќе биде пратена
# на PERL скриптата, се печати на екран нејзиното име и колку различни датуми се пронајдени.

#!/bin/bash

for dat in $@: #site arguments prateni
do
    jaIma=$(find . -type f -name $dat)
    if [ -n "$jaIma" ];then
        valid=$(cat $jaIma | grep "[1-31]\-[1-12]\-[0-9][0-9][0-9][0-9]")
        if [ -n valid ];then 
            rez=$(k1.py $jaIma) #povikuvame python script i prv argument imeto
            #rez go sodrzi output-ot na python skriptata
            d="${dat}_out"
            rez1=$(cat $d | awk 'print $1' | uniq -u | wc -l)
            #awk 'print $1'-> Extracts the first column from each line of the file.
            #uniq -u -> filters unique values in first coloumn
            #wc -l -> counts number of unique lines
            echo "$dat $rez1"
        fi
    fi
done
