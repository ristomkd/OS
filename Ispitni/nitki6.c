/* Да се напише програма во C која работи со процеси и нитки. Главната програма (родител процесот) 
треба да креира дете процес, на кого ќе му прати низа од 100 цели броеви. Дете процесот најпрво треба 
да ја пополни низата од 100 цели броеви со нули. Потоа, дете процесот треба да креира N нитки (N се 
внесува од тастатура во родител процесот), притоа на секоја нитка дете процесот ѝ испраќа (како 
аргументи) два случајни броеви К1 и К2 кои што го кажуваат опсегот (долна и горна граница) на 
елементи од низата за кои е задолжена нитката. Секоја нитка прави инкремент (зголемување на 
вредноста за 1) на елементите од низата во опсег од К1 до К2 (секоја нитка има случајни сопствени 
вредности за К1 и К2, притоа К1 секогаш треба да биде помал од К2). Откако ќе завршат со работа сите 
нитки, главната  нитка (дете процесот) печати на екран колку елементи од низата имаат преклопување 
кај две или повеќе нитки во нивниот опсег (елементите од низата имаат вредност поголема од 1). 
Родител процесот завршува откако дете процесот ќе заврши. Генерирањето на случајни броеви се прави 
со помош на функцијата rand( ). */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>
#include <time.h>

#define MAX_NITKI 10
int niza[100];

typedef struct{
    int id;
    int k1;
    int k2;

}sani;

void *funkcija(void *t){
    sani id=*((sani *)t);
    for(int i=id.k1;i<id.k2;i++){
        niza[i]+=1;
    }
    pthread_exit(NULL);
}

int main(int argc,char* argv[]){
    int N;
    pid_t dete;
    printf("Vnesi go N");
    scanf("%d", &N);
    dete=fork(); 
    if(dete!=0){
        wait(NULL);
        printf("roditel process zavrsuva\n");
    } else{ //dete process
        for(int i=0;i<100;i++){
            niza[i]=0;
        }
        pthread_t nitki[N];
        srand(time(NULL)); //random integer different seeds each time
        sani t[N];
        for(int i=0;i<100;i++){
            t[i].id=i;
            t[i].k1=rand() % 50; //0-49
            t[i].k2=50 + rand()%50; //50 +(0-49)
            int rc1=pthread_create(&nitki[i],NULL,funkcija,(void *)&t[i]);
            if (rc1){
                printf("Greska");
                return 0;
            }
        }

        for(int i=0;i<N;i++){
            pthread_join(nitki[i],NULL);
        }

        int brojac=0;
        for(int i=0;i<100;i++){
            if(niza[i]>1){
                printf("%d",niza[i]);
                brojac++;
            }
        }

        printf("Vkupno ima %d", brojac);
    }
    return 0;
}
