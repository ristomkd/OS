#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_NITKI 5

int niza[100];
int N, K, found = 0;

void *prebaraj(void *t) {
    int id = *((int *)t);

    for(int i = 0; i < N; i++) {
        if(found) {
            pthread_exit(NULL);
        }

        int index = rand() % N;

        if(niza[index] == K) {
            printf("Proces 1: Nitkata %d go najde brojot %d na pozicija %d\n", id, K, index);
            found = 1;
            kill(0, SIGTERM);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    if(argc < 3) {
        printf("Nedovolen broj na argumenti");
        exit(-1);
    }

    N = atoi(argv[1]);
    K = atoi(argv[2]);

    FILE *file = fopen("dat.txt", "r");
    if(!file) {
        perror("Datotekata ne postoi");
        exit(-1);
    }

    for(int i = 0; i < N; i++) {
        fscanf(file, "%d", &niza[i]);
    }
    fclose(file);

    pthread_t nitki[MAX_NITKI];
    int t[MAX_NITKI];
    int rc1;

    for(int i = 0; i < MAX_NITKI; i++){
        t[i] = i;
        rc1 = pthread_create(&nitki[i], NULL, prebaraj, (void *)&t[i]);

        if(rc1) {
            printf("Neuspesno kreiranje na nitka %d \n", i);
            exit(-1);
        }
    }

    for(int i = 0; i < MAX_NITKI; i++) {
        rc1 = pthread_join(nitki[i], NULL);

        if (rc1) {
            printf("ERROR; return code from pthread_join() is %d\n", rc1);
            exit(-1);
        } 
    }

    if(!found) {
        printf("Proces 2 ne go najde brojot %d\n", K);
    }

    return 0;

}