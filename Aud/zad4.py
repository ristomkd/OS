# Да се напише Python скрипта со име „prva.plx“ која како аргументи добива најпрво збор кој ќе го
# пребарува, опција (знаменце) и име на датотека во која ќе се прави пребарувањето. Скриптата треба да
# го пребара зборот (што се праќа како прв аргумент) во зависност од опцијата (што се праќа како втор
# аргумент) во датотеката (чие име се праќа како трет аргумент). Опцијата може да биде „l“, „w“ или „f“,
# притоа опцијата „l“ значи дека треба да се вратат броевите од линиите во кои е пронајден зборот,
# „w“ како резултат враќа колку зборови биле пронајдени пред зборот што се бара, и опцијата „f“ враќа
# колку пати е пронајден зборот во датотеката. Доколку зборот го нема во датотеката, опцијата „l“ враќа -
# 1, додека пак опциите „w“ и „f“ враќаат соодветно вредност 0. Зборовите се одделени еден од друг со
# празно место. Доколку добие невалидна опција, скриптата прекинува со извршување.

import sys

if len(sys.argv)<4:
    print("Nedovolno argumenti")
    sys.exit(-1)

zbor=sys.argv[1] #zborot koj go barame
zname=sys.argv[2]
if zname not in ['l', 'w', 'f']: #dokolku zname ne e edno od ovie navedeni vo nizata
    print("Nevaliden flag")
    sys.exit(-1)

# "l" значи дека треба да се вратат броевите од линиите во кои е пронајден зборот - -1
# "w" како резултат враќа колку зборови биле пронајдени пред зборот што се бара - 0
# "f" колку пати е пронајден зборот во датотеката, доколку го нема враќа 0
l=w=f=0
dat=open(sys.argv[3],"r")
found = False
for lines in dat.readlines():
    lines=lines.strip() #remove whitespace
    zborovi=lines.split(" ")
    line_found = False
    for z in zborovi:
        if z == zbor:
            if not line_found: #if (line_found == False)
                line_found=True
                l=l+1 #kolku linii sodrzat takov zbor
            if zname == "l":
                print ("l")
            elif zname =="w":
                print("w")
            else:
                f=f+1 #kolku pati e pronajden zborot
                found=True
        w=w+1 #kolku zborovi se najdeni pred toj zbor
   
if zname == "f":
    print(f)

if zname == "w":
    print(w)

if zname == "l":
    print(l)
    
if f==0:
    if zname == "l":
        print(-1)
    if zname =="w":
        print(0)
    else:
        print(0)




