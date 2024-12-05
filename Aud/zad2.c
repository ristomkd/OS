/* Да се напише програма која како аргумент добива команда која треба
да ја изврши.
 Татко процесот треба на екран да ги испишува секундите поминати од
започнување на програмата до крајот.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(int argc,char* argv[]){

    if(argc<2){
        printf("Nedovolen broj argumenti");
        exit(-1);
    }
    int sekundi=0;
    pid_t dete= fork();
    if(dete == 0){
        execvp(argv[1],&argv[1]);
        printf("Greska pri execvp");
    }
    while(waitpid(dete,NULL,WNOHANG)!=dete){
        sekundi++;
        sleep(1);
    }
    printf("Pominati se %f sekundi",sekundi);
    return 0;
}