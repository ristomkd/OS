#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_NITKI 5
int N,K,found=0;
int niza[100];
pid_t parent_pid,dete;
//n-broevi vo niza, k-broj koj treba da se bara vo taa niza
void terminate_other_process(pid_t other_pid) {
    kill(other_pid, SIGTERM);
    printf("Процесот со PID %d е убиен.\n", other_pid);
}

void *prebaraj(void *t){
    int id=*((int *)t);

    for(int i=0;i<N;i++){
        if(found){
            pthread_exit(NULL); // Exit if another thread found the number
        }

        int index=rand() % N;

        if(niza[index]==K){
            printf("Proces 1: Nitkata %d go najde brojot %d na pozicija %d",id,K,index);
            found=1;
             if (getpid() == parent_pid) {
                terminate_other_process(dete);
            } else {
                terminate_other_process(parent_pid);
            }  // Terminate the process (including all threads)
        }
    }
    pthread_exit(NULL);
}
int main(int argc,char* argv[]){

    if(argc<3){
        printf("Nedovolen broj argumenti");
        exit(-1);
    }
    N=atoi(argv[1]); //string to integer
    K=atoi(argv[2]);

    FILE *file=fopen("dat.txt","r");
    if(!file){
        printf("Datotekata ne postoi");
        exit(-1);
    }

    for(int i=0;i<N;i++){
        fscanf(file,"%d",&niza[i]); //Reads N integers into Niza from file
    }
    pthread_t nitki[MAX_NITKI];
    int t[MAX_NITKI];
    int rc1;

    parent_pid=getpid();
    dete=fork();

    if(dete!=0){
        wait(NULL);
        printf("Processot 1 zavrshi\n");
    }
    else{
         execl("./zad15","zad15",argv[1],argv[2],NULL);
         printf("Neuspesno startuvanje na vtorata programa");
         exit(-1);
    }
    
    for(int i=0;i<N;i++){
        t[i]=i;
        rc1=pthread_create(&nitki[i],NULL,prebaraj,(void *)&t[i]);
        if(rc1){
            printf("Neuspesno kreiranje na nitka");
            exit(-1);
        }
    }
    for(int i=0;i<N;i++){
        rc1=pthread_join(nitki[i],NULL);
        if(rc1){
            printf("Error");
            exit(-1);
        }
    }

    if(!found){
        printf("Process 1 ne go najde brojot %d\n", K);
    }
    return 0;
}