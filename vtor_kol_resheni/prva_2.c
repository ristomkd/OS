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
#define SHM_KEY 1234
#define MAX_PROCESSES 200

int main(int argc, char **argv){

    char *mem;
    int id,fd;
    pid_t procesi[MAX_PROCESSES];
    int process_counter=0;

    id = shmget(SHM_KEY,SHM_SIZE, 0644 | IPC_CREAT);
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

  for (i = 0; i < 6; i++)
  {
    if (mem[0] == '1')
      break;
    fflush(stdout);
    printf("Spijam 10 sekundi");
    sleep(10);
  }
  if (i == 6 && k == 1)
  {
    printf("Pospav 60 minuti, probuvam so mmap");
    shmdt(mem);
    if ((fd = open(dat, O_RDWR | O_CREAT, 00666)) == -1)
    {
      printf("neuspesno otvoranje na datotekata");
      return 0;
    }
    // kreiranje na memorija za novo-kreiraniot file
    if (ftruncate(fd, 1024) == -1)
    {
      printf("neuspesno proshiruvanje na memorijata");
      return 0;
    }
    mem = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED)
    {
      printf("neuspesno mapiranje na memorijata");
      return 0;
    }
    k = 2;
    for (i = 0; i < 6; i++)
    {
      if (mem[0] == '1')
        break;
      sleep(10);
    }
  }
  if (i < 6)
  {
    printf("procitav naredba %s, ja izvrshuvam", mem + 1);
    execlp(mem + 1, mem + 1, NULL);
  }

    for (int j =0;j<MAX_PROCESSES;j++)

    k == 1 ? shmdt(mem) : munmap(mem, 1024);

    return 0;
}
