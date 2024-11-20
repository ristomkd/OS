#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Да се напише програма која ќе креира 5
нитки. Секоја од нитките да го отпечати на
екран својот реден број. Дали при секое
извршување на програмата, ист е редоследот
на печатење на екран? Зошто? Од што
зависи? */
void *funkcija(void *t){
    int i= *((int *)t);
    printf("Jas sum nitka %lu dobiv broj %d\n",pthread_self(),i);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    pthread_t threads[10]; // Array to hold thread IDs.
    int rc1;    // Return code for thread-related functions
    long t;
    void *status;
    int b[5]; // Array to hold integers passed to threads.
    for(t=0;t<5;t++){
        printf("Main: kreiranje nitka %ld\n",t);
        b[t]=t;
        rc1=pthread_create(&threads[t],NULL,funkcija,(void *)&b[t]);
        if(rc1){
            printf("ERROR; return od pthread_create() e %d\n", rc1);exit(-1);
        }
    }

    for(t=0;t<5;t++){
        rc1=pthread_join(threads[t], &status);
        if (rc1){
            printf("ERROR; return code from pthread_join() is %d\n",rc1);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having status of %ld\n",t,(long)status);
    }
    pthread_exit(NULL);

    return 0;
}