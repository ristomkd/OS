# Да се напише SHELL скрипта која како аргумент добива име на ПЕРЛ скрипта, збор за 
# пребарување и листа од имиња на датотеки. Доколку не добие како прв аргумент име на ПЕРЛ 
# скрипта (аргумент што завршува на .plx) тогаш зема како име на скрипта „prva.plx“. Shell 
# скриптата треба да провери дали има ПЕРЛ скрипта со такво име во тековниот директориум 
# или поддиректориумите и доколку нема, завршува Shell скриптата со извршување. Доколку 
# постои ПЕРЛ скрипта со такво име (тековниот директориум или поддиректориумите), тогаш 
# Shell скриптата треба со помош на PERL скриптата, да најде и отпечати на екран, колку пати ќе 
# го пронајде зборот (што се праќа како втор аргумент на Shell) за сите датотеки што се праќаат 
# како аргументи (од трет аргумент па натаму). На крај скриптата треба да отпечати колку 
# вкупно бил пронајден зборот во сите датотеки. 

if [ $# -lt 3];then
    echo "Not enough arguments passed"
    exit 1
fi

python_script="$1"
if [ [! "$python_script" =~ \.py$] ];then
    python_script="prva.py"

py = $(find . -type f -name "prva.py")
if [ ! -f "prva.py" ];then
    echo "Ne postoi datoteka so vakvo ime" 
    exit 1
fi

search_word="$2" 
total_count=0

for file in "$@";do
    if [ ! -f "$file"];then
        echo "File '$file' does not exist"
        continue
    fi
    #povikuvame python script da go bara zborot vo toj file
    execute=$(Python "python.py" "$file" "$search_word") 
    if [ $? -eq 0];then
        echo "File '$file' contains the word '$search_word' $count times."
        total_count=$((total_count + execute))
    else
        echo "Error"
    fi
done

echo "Total number of occurences: $total_count"
