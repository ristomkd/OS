#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main(int argc, char **argv){

    key_t kluc = 1234;
    char *dat = "dat.txt";
    int k=0;
    int id,fd;
    char *mem;

    if(argc<2){
        printf("Nedovolen broj argumenti!");
        exit -1;
    }
    id = shmget(kluc, 1024, 0644 | IPC_CREAT);
    if(id != -1){
        mem = shmat(id, NULL, 0);
    }
    if(id == -1 || mem ==(char *) -1){
        printf("neuspesno prikacuvanje na memorijata, probuvam so mmap");
        if( (fd = open(dat, O_RDWR | O_CREAT, 00666)) == -1){
            printf("neuspesno otvaranje na datoteka");
            return -1;
        }

        if(ftruncate(fd,1024) == -1){
            printf("neuspesno prosiruvanje na memorija");
            return 0;
        }

        mem = mmap(NULL,1024,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
        if(mem == MAP_FAILED){
            printf("neuspesno mapiranje na memorijata");
            return 0;
        }
        k=2; //memorisko mapiranje
        
    } else {
        k = 1; //so shared memory
    }
    strncpy(mem+1, argv[1],SHM_SIZE-1);
    mem[0]='1'; //1 - nesto e zapisano
    mem[SHM_SIZE - 1] = '\0';

    k == 1 ? shmdt(mem) : munmap(mem, 1024);

    return 0;
}