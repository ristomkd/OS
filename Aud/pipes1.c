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

int main(int argc, char *argv[]){
    
    pid_t dete;
    int mypipe[2]; // 0 - read , 1 - write
    char mem[512];
    int fd, broj;

    if(pipe(mypipe)){
        printf("pipe failed\n");
        return EXIT_FAILURE;
    }
    // roditel -> 1 (stdout) -> 0(stdin) -> dete
    pid = fork();
    if (pid == 0){
        close(mypipe[1]); 
        if(dup2(mypipe[0],0)==-1){
            printf("neuspeav da dupliciram vo 0\n");
            return 0;
        }
        scanf("%s%d",mem,&broj);
        printf("#%s%d",mem,broj);

        return EXIT_SUCCESS;
    }
    else if (pid<0){
        printf("Neuspesen fork");
        return EXIT_FAILURE;
    } else {
        close(mypipe[0]);
        if(dup2(mypipe[1],1)==-1){
            printf("Neuspeav da dupliciram vo 1\n");
            return 0;
        }
        printf("%d\n",15);
        return EXIT_SUCCESS;
    }
    return 0;
}