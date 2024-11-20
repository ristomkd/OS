# Да се напише Python скрипта која како аргументи од командна линија добива имиња на датотеки.
 # Скриптата треба да ги измине датотеките и да провери колку различни валути на пари ќе најде. Знаците
 # на валутите кои што се пребаруваат се: „$“ „€“ „£“ „kn“ „kr“ „Rp“ „CHF“. Секоја валута започнува со
 # знакот на валутата, по кое што следи сумата на истата (одделена со празно место). Доколку после
 # валутата нема бројка, тогаш валутата не се зема во предвид. Сите валути што ќе бидат пронајдени во
 # датотеката се собираат и се добива вкупна сума по валута. За секоја валута што била пронајдена во
 # датотеката, му се дозволува на корисникот да внесе колку денари е истата (не се внесува за оние валути
 # кои што не биле пронајдени во тековната датотека). На крајот од изминувањето на датотеката да се
 # отпечати вкупната сума (во денари) што била пронајдена во датотеката. Скриптата, на крај треба да
 # отпечати кои валути биле пронајдени во сите датотеки.

import sys
if (len(sys.argv)<2):
    print("Nedovolno argumenti")
    sys.exit(-1)
niza=['$','€','£','kn','kr','Rp','CHF']
niza1=['0','1','2','3','4','5','6','7','8','9']

found_in_all=set()

sumaDollar = sumaEuro = sumaPound = sumaKn = sumaKr = sumaRp = sumaCHF = 0  
cnt1, cnt2, cnt3, cnt4, cnt5, cnt6, cnt7= False

for dat in sys.argv[1:]:
    d=open(dat,"r")
    d=d.read()
    words=d.split(" ")
    found_in_file = set()
    vkupnodenari=0
    d.close()
    for z in range(len(words)-1):
        currentword=words[z]
        nextword=words[z+1]
        if nextword.isdigit():
            amount=float(nextword)
        if currentword not in niza:
            print("Nema validna valuta")
            continue
        if currentword in niza and nextword.isdigit(): #nextword.replace('.', '').isdigit() za decimalni zborovi
            if currentword == "$":
                sumaDollar+=amount
                cnt1=True
                found_in_file.add("$")
            elif currentword == "€":
                sumaEuro+=amount
                cnt2=True
                found_in_file.add("€")
            elif currentword == "£":
                sumaPound+=amount
                cnt3=True
                found_in_file.add("£")
            elif currentword == "kn":
                sumaKn+=amount
                cnt4=True
                found_in_file.add("kn")
            elif currentword == "kr":
                sumaKr+=amount
                cnt5=True
                found_in_file.add("kr")
            elif currentword == "Rp":
                sumaRp+=amount
                cnt6=True
                found_in_file.add("Rp")
            elif currentword == "CHF":
                sumaCHF+=amount
                cnt7=True
                found_in_file.add("CHF")
    
    if cnt1 and "$" in found_in_file:
        print("Najdenata valuta e '$' so suma "+sumaDollar)
        kurs = float(input("Vnesi kurs za dolar vo denari: "))
        vkupnodenari += sumaDollar * kurs
    if cnt2 and "€" in found_in_file:
        print("Najdenata valuta e '€' so suma "+sumaEuro)
        kurs = float(input("Vnesi kurs za evro vo denari: "))
        vkupnodenari += sumaEuro * kurs
    if cnt3 and "£" in found_in_file:
        print("Najdenata valuta e '£' so suma "+sumaPound)
        kurs = float(input("Vnesi kurs za funta vo denari: "))
        vkupnodenari += sumaPound * kurs
    if cnt4 and "Kn" in found_in_file:
        print("Najdenata valuta e 'kn' so suma "+sumaKn)
        kurs = float(input("Vnesi kurs za kuna vo denari: "))
        vkupnodenari += sumaKn * kurs
    if cnt5 and "Kr" in found_in_file:
        print("Najdenata valuta e 'kr' so suma "+sumaKr)
        kurs = float(input("Vnesi kurs za kruna vo denari: "))
        vkupnodenari += sumaKr * kurs
    if cnt6 and "Rp" in found_in_file:
        print("Najdenata valuta e 'Rp' so suma "+sumaRp)
        kurs = float(input("Vnesi kurs za rupija vo denari: "))
        vkupnodenari += sumaRp * kurs
    if cnt7 and "CHF" in found_in_file:
        print("Najdenata valuta e 'CHF' so suma "+sumaCHF)
        kurs = float(input("Vnesi kurs za franki vo denari: "))
        vkupnodenari += sumaCHF * kurs
    
    print(f"\nVkupna suma vo denari za datoteka {dat}: {vkupnodenari:.2f} MKD")
    
    if dat == sys.argv[1]:
        found_in_all = found_in_file
    else:
        # За следните датотеки, го задржуваме пресекот
        found_in_all = found_in_all.intersection(found_in_file)

# На крај печатиме кои валути се најдени во СИТЕ датотеки
print("\nValuti pronajdeni vo SITE datoteki:")
if found_in_all:
    for valuta in found_in_all:
        print(valuta)
else:
    print("Nema valuti koi se pronajdeni vo site datoteki")
    


        
