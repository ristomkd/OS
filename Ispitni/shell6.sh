`#Da se napishe SHELL skripta koja treba da gi najde site datoteki vo tekovniot direktorium i 
poddirektorium, koi imaat nastavka ".ip". Potoa koristejki pajton skripta da se generiraat site mozni IP addressi, 
za sekoja Ip adresa, da se proveri dali ima pristap do istata, i analizata da se ispishe na ekran(da se ispishe
sekoja IP adresa, i do istata OK ili NOT vo prodolzenie)`

#Proverkata za pristap -> ping -c | $IP> /dev/null 2>&1;

file=$(find . -type f -name "*.ip")
#file=$(ls -a | grep ".*\.ip$")
ip1=()
for files in $file;do
    execute=$(Python "piton.py" "$files")
    for ip in $execute;do
        ping -c 1 "$ip" > /dev/null 2>&1
        if [ $? -eq 0];then
            echo "$ip OK"
        else
            echo "$ip NOT OK"
        fi
    done
done