/*  Да се напише програма во C која работи со процеси и нитки. Главната програма (главната нитка) како
 аргумент добива име на влезна датотека. Главната нитка треба да креира онолку нитки колку што треба,
 така што, секоја нитка да добие по 10 линии од влезната датотека (нема повеќе од 1000 линии, а притоа
 последната нитка може да добие и помалку од 10 линии). Секоја една од нитките, ги изминува своите 10
 линии од датотеката и брои колку има големи а колку мали букви. Откако ќе завршат нитките, главната
 нитка печати на екран колку секоја нитка нашла големи и мали букви и печати колку вкупно големи и
 мали букви биле пронајдени. Не е дозволено содржината на целата датотека да биде прочитана во низа
 т.е. секоја од нитките мора да работи со FILE * покажувач за изминување на датотеката т.е. на линиите
 од датотеката. */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>
#include <time.h>

#define MAX_LINES 1000
#define BUFFER_SIZE 1024
#define LINES_PER_THREAD 10

typedef struct{
    FILE *file;
    int id; //id na nitkata
    int uppercase_count;
    int lowercase_count;
    int lines_to_read;
    int startline;
} ThreadARG;

void *baraj(void *arg){
    ThreadARG arg1=*((ThreadARG *)arg);
    char line[BUFFER_SIZE];
    int uppercase_count;
    int lowercase_count;
    // Move the file pointer to the starting line for this thread
    for(int i=0;i<arg1.startline;i++){
       fgets(line,BUFFER_SIZE,arg1.file);
    }
    //Process each line
    for (int i = 0; i < arg1.lines_to_read; i++) {
        if (fgets(line, BUFFER_SIZE, arg1.file) == NULL) {
            break; // Reached end of file
        }
    for(int j=0; line[j]!='\n';j++){
        if(line[j]>='A' && line[j]<='Z'){
            uppercase_count++;
        }
        else if(line[j]>='a' && line[j]<='z'){
            lowercase_count++;
        }
    }

    arg1.lowercase_count=lowercase_count;
    arg1.uppercase_count=uppercase_count;
    // Print the results for this thread
    printf("Nitka %d: Golemi bukvi = %d, Mali bukvi = %d\n", 
           arg1.id, uppercase_count, lowercase_count);
    pthread_exit(NULL);
}
}

int main(int argc,char*argv[]){

    if (argc<2){
        printf("Nema dovolno argumenti");
        exit(-1);
    }

    FILE *file = fopen(argv[1],"r");
    if(!file){
        printf("Greska pri otvaranje na datoteka");
        exit(-1);
    }
    //presmetaj linii vo datoteka
    int total_lines=0;
    char lines[BUFFER_SIZE];
    while(fgets(lines,sizeof(lines),file)!=NULL){
        total_lines++; 
    }
    rewind(file); //vrati pokazuvac na pocetok na datoteka

    int num_threads=(total_lines + LINES_PER_THREAD -1 )/LINES_PER_THREAD;
    pthread_t nitki[num_threads];
    ThreadARG arg[num_threads];
    int rc1;
    for(int i=0;i<num_threads;i++){
        arg[i].id=i;
        arg[i].file=file;
        arg[i].startline=i*LINES_PER_THREAD;

        if(i==num_threads-1){ //sme na posledna nitka
            // Последна нитка може да чита помалку од 10 линии
            arg[i].lines_to_read=total_lines-(i*LINES_PER_THREAD);
        }else{
            arg[i].lines_to_read=LINES_PER_THREAD;
        }

        rc1=pthread_create(&nitki[i],NULL,baraj,(void *)&arg[i]);
        if(rc1){
            printf("Greska pri kreiranje na nitka");
            exit(-1);
        }
    }

    int total_uppercase=0;
    int total_lowercase=0;
    for(int i=0;i<num_threads;i++){
        pthread_join(nitki[i],NULL);
        total_uppercase+=arg[i].uppercase_count;
        total_lowercase+=arg[i].lowercase_count;
    }

    printf("Total uppercase letters: %d", total_uppercase);
    printf("Total lowercase letters: %d", total_lowercase);

    fclose(file);
    return 0;
}