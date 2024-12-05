# Да се напише Python скрипта која добива низа од аргументи од командна линија. Скриптата
# мора да се повика со најмалку два аргументи, инаку се печати порака за грешка.
# Аргументите се имиња на текстуални датотеки. Скриптата треба да ја измине содржината
# на секоја една од датотеките и да направи замена на првиот со последниот, вториот со
# претпоследниот и т.н. Доколку зборовите што се заменуваат се исти (истиот збор) тогаш да
# не се прави замена. Зборовите се одделени еден од друг со празно место. Замената се
# враќа назад во датотеките.

#!/usr/bin/python3

import sys

length=len(sys.argv) #dolzhina na argumenti
if(length<2):
        print("Error\n")
        sys.exit(-1)

else:
        for i in range(length-1): #da ni otide do posledniot argument
                file=open(sys.argv[i+1], "r") #ne 0, bidejki 0 e samata skripta
                d=file.read() #go chita celiot file
                words=d.split()
                l=0
                r=len(words)-1
                while(l<r):
                        if(words[l]==words[r]):
                                l+=1
                                r-=1
                        else:
                                tmp=words[l]
                                words[l]=words[r]
                                words[r]=tmp
                                l+=1
                                r-=1
                file=open(sys.argv[i+1], "w")
                for j in range(len(words)):
                        file.write(words[j]+ " ")
                                