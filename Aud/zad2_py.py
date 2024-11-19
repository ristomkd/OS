# Да се напише Python скрипта која од командна линија добива три
# датотеки. Скриптата треба да ги испреплети двете датотеки и
# излезот да го запише во трета датотека. Најпрво ќе се смести
# првата линија од првата датотека, па првата линија од втората и
# т.н. Дополнително, паралелно да се изврши печатење на екран
# излезот што се запишува во третата датотека.

import sys

length=len(sys.argv)
if(length<4):
    print("Ne vnesovte dovolno argumenti")
    sys.exit(-1)

file1=open(sys.argv[1],"r")
file2=open(sys.argv[2],"r")
file3=open(sys.argv[3],"w")

data1=file1.read()
data2=file2.read()
d1=data1.split(".")
d2=data2.split(".")
if len(d1)>len(d2):  #koj file ima povekje rechenici
    min=d2
    max=d1
else:
    max=d2
    min=d1
i=0
for l1 in min: #nekjeme null redovi
    file3.write(l1) 
    file3.write(max[i]) # iterira niz pogolemiot file
    print(l1)
    print(max[i])
    i+=1
while i<len(max):
    print(max[i])
    i+=1

