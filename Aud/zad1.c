/* Да се напише програма која како аргумент добива команда која
треба да ја изврши.
Програмата треба да изврши замена на стандардниот знак „&“
со „%“ за започнување на програма како позадински или преден
процес.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(int argc, char* argv[]){

    if (argc==1){ 
        printf("Nedovolen broj argumenti"); 
        exit(-1);
        }
    int len=strlen(argv[argc-1]); // go ziame length-ot na posledniot argument /.skirpta.c firefox &
    
    int towait=1;
    if(len==1&&argv[argc-1][0]=='&'){ 
        argv[argc-1][0]='%';
        towait=0;
    } else if(argv[argc-1][len-1]=='&'){
        argv[argc-1][len-1]='%';
        towait=0;
    }
    pid_t dete= fork();
    if(dete == 0){
        execvp(argv[1],&argv[1]);
        printf("Greska pri execvp");
    }
    if(towait){ //dokolku najde & da se izgasi parent process, i argumentot daden da se izvrshuva vo pozadina
        wait(NULL);
    }
    return 0;
}