import sys
if len(sys.argv)<4:
    print("Nedovolno argumenti")
    sys.exit()
zbor=sys.argv[1]
zname=sys.argv[2]
if zname not in ["l", "w", "f"]: #sakame da najdeme edno od ovie znaminja
    print("Nevalidno zname")
    sys.exit()
    
l=w=f=0 
dat=open(sys.argv[3],"r")
for line in dat.readlines():
    line.trim()
    zborovi=line.split(" ") 
    for z in zborovi:
        if zbor == z:
            if zname == "l":
                print(l)
            elif zname == "w":
                print(w)
            else:
                f=f+1
        w=w+1
    l=l+1

if zname == "f":
    print(f)

if f == 0:
    if zname == "l":
        print(-1)
    if zname == "w":
        print(0)