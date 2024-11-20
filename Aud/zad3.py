# Да се напише Python скрипта која како аргумент добива име на влезна датотека. Скриптата треба да
# креира излезна датотека со исто име како и влезната, само со наставка “_out”. Скриптата треба да ја
# измине влезната датотека линија по линија, и во излезната датотека да ја запише линијата, така што
# доколку во линијата текст се наоѓа датум, датумот да дојде прв во линијата, па потоа, без менување на
# редоследот, да дојде и останатиот текст од линијата. Форматот на датумот е “DD-MM-YYYY”, притоа,
# доколку има повеќе од еден датум, се запишуваат во излезната датотека онолку линии колку што има
# различни датуми во влезната линија, притоа текстот што следи е без датуми. Доколку скриптата се
# повика со втор аргумент и доколку вториот аргумент е валиден датум, тогаш дополнително и на екран
# се печатат оние линии каде што го има тој датум. Зборовите во датотеката се одделени со празно место.  

import sys

if len(sys.argv)<2:
    print("Nedovolno argumenti")
    sys.exit(-1)

flag=0
dat=sys.argv[1]

if len(sys.argv)>2:
    if len(sys.argv[2].split("-")==3): #if valid date is provided ['12' '12' '2012']
        flag=1

file=open(dat,"r")
niza=[] #ke stavame lines koi sodrzat specific date 
lines=""
for l in dat.readlines():
    l=l.strip() #trga whitespace

    zborovi=l.split(" ")
    for z in zborovi:
        if len(z.split("-")==3):
            niza.append(z) # sme nashle validen tamu go smestuvame vo nizata od datumi
        else:
            lines=lines + " " + z
        if len(niza)==0:
            print(lines)

    for z in niza: # ['12-12-2021' '15-10-2003' '16-16-2016' '21-12-2003']
        print(z+" "+ lines)

if flag==1:
    if sys.argv[2] in niza:
            niza.append(lines)
if flag==1:
    for z in niza:
        print(sys.argv[2]+" "+ z)
