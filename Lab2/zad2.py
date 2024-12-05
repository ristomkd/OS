# Да се напише Python скрипта која како аргументи од командна линија добива име на
# датотека и знаменце (flag). Датотеката го чува излезот од ls –al наредбата на тековниот
# директориум (прикажано на сликата). Доколку скриптата се повика со знаменце „–d“
# тогаш на екран треба да се испишат различните датуми на кои биле
# креирани/модифицирани директориумите или датотеките сместени во влезната датотека.
# Доколку скриптата се повика со знаменце „-f“, тогаш треба, за секој датум да се отпечати
# колку датотеки или директориуми биле креирани/модифицирани.

#!/usr/bin/python3

import sys

if len(sys.argv)!=3: #sakame 2 argumenti ekstra (/skripta.py primer.txt -d or -f)
    print("Greska")
    sys.exit(-1)

filename=sys.argv[1]
flag=sys.argv[2]

file=open(filename, "r")
lines=file.readlines() 
file.close() #not necessary

dates={} #empty 
for line in lines[1:]: #exclude header   
    parts=line.split() # [ 'drwxr-xr-r' '4' 'root' 'root' '4096' '2011-12-21' '11:35' 'yarfs' ] 
    date=' '.join(parts[5:7]) # 5i6 gi zima excludes 7
    if flag == "-d":
        if date not in dates:
            dates[date]=1
    elif flag == "-f":
        if date in dates:
            dates[date]+=1
        else:
            dates[date]=1

if flag =="-d":
    for date in dates.keys():
        print(date)
elif flag =="-f":
    for date,count in dates.items():
        print(f" {dates}:{count}")
else:
    print("Greska")


