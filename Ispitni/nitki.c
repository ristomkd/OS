#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include<sys/wait.h>
/*
Glavnata programa (roditel processot) dobiva niza od naredbi koi treba da gi izvrshi kako argumenti
od komandna linija. Roditel processot treba, najprvo, da kreira onolku deca procesi kolku shto ima naredbi
navedeno od komandna linija(naredbite se bez argumenti). Potoa treba da se kreira onolku nitki, kolku sto 
ima naredbi, taka shto sekoja nitka ke ceka i ke broi kolku sekundi mu bilo potrebno na soodvetniot proces
da zavrshi. Toa znaci deka prvata nitka ke bide zadolzena za prvata naredba(t.e. za prviot process),
vtorata za vtoriot itn. Sekoja nitka broi kolku vreme se izvrshuval nejziniot process(naredba) i koga ke 
zavrshi, kazuva kolku vkupni sekundi mu trebalo da zavrshi. Potoa i samata nitka zavrshuva. Otkako ke 
zavrshat site processi/nitki, togash glavniot process/nitka, pecati na ekran kolku vreme i trebalo na 
sekoja naredba da se izvrshi.
*/
pid_t deca[100];
int vreme[100];

void *funkcija(void *t){
    int id=*((int *)t);
    int s=0;
    // cekame specific dete da zavrsi
    while(waitpid(deca[id],NULL,WNOHANG)!=deca[id]){
        sleep(1);
        s++;
    }
    vreme[id]=s;
    pthread_exit(NULL);
}
int main(int argc,char*argv[]){
    int rc1;
    int N=argc-1; //number of commands
    pthread_t nitki[N];
    int t[N];

    //CREATE CHILD PROCESSES
    for(int i=0;i<N;i++){
        deca[i]=fork();
        if(deca[i]==0){
            execlp(argv[i+1],&argv[i+1],NULL);
            perror("Error\n");
            exit(1);
        }
        else if(deca[i]<0){
            printf("Fork failed");
            exit(1);
        }
    }
    //CREATE THREADS
    for(int i=0;i<N;i++){
        t[i]=i;
        int rc1=pthread_create(&nitki[i],NULL,funkcija,(void *)&t[i]);
        if(rc1){
            printf("Error\n");
            exit(1);
        }
    }
    //WAIT FOR ALL THREADS
    for(int i=0;i<N;i++){
        pthreads_join(nitki[i],NULL);
    }

    //Printaj gi vreminjata na cekanje
    for(int i=0;i<N;i++){
        printf("Command '%s' i trebashe %d",argv[i+1],vreme[i]);
    }

    return 0;
    }

