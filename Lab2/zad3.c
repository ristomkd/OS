/* Да се напише C програма која ќе направи N пати извршување на некоја наредба. Родител
процесот најпрво од тастатура го вчитува бројот колку пати ќе се изврши наредбата.
Самата наредба се внесува како аргумент од командна линија и може да има непознат
(променлив) број на аргументи. Родител процесот потоа ги креира останатите N процеси,
секој еден од тие N процеси ја извршува наредбата, и чека секој еден од нив да заврши.
Кога ќе заврши и последниот процес, родителот ја испишува пораката: “Zavrshuva process 0”.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int N;
    scanf("%f", N);

    if(argc<2){
        printf("Nedovolen broj argumenti");
        exit(1);
    }

    for(int i=0;i<N;i++){
        pid_t dete = fork();
        if(dete == 0){
            execvp(argv[1], &argv[1]);
            printf("Greska pri execvp");
            exit(1);
        }
    }
    //roditel ceka site deca da zavrshat
    for(int i=0;i<N;i++){
        wait(NULL);
    }
    printf("Zavrsuva process 0\n");
    return 0;
}

