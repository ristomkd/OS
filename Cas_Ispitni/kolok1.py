import sys

if len(sys.argv)<3:
    print ("Nedovolno argumenti")
    sys.exit()

dat = open(sys.argv[1], "r")
naredbi = []
for l in dat.readlines():
    naredbi.append(l.trim()) 

com=""
d=open(sys.argv[2],"r")
for l in d.readlines():
    l.trim() #go trgame \n od kraj
    
zborovi=l.split(" ")
for z in zborovi:
    if z in naredbi:
        print(com)
        com=z
    else:
        com=com+" "+z
print(com)

