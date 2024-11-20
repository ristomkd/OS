#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>
#include <time.h>
#define MAX_FILES 3
#define BUFFER_SIZE 1024
#define MAX_WORD 100
/* Да се напише програма во C која работи со процеси и нитки. Програмата (главната 
нитка) како аргументи од командна линија добива збор што се пребарува и листа од 
имиња на датотеки. Доколку не добие листа од датотеки од командна линија (добие 
само збор за пребарување), програмата треба да му дозволи да внесе имиња на 3 
датотеки од тастатура. Доколку нема ни збор за пребарување, најпрво го внесува зборот 
од тастатура, а потоа имињата на 3те датотеки. За секоја датотека во која се прави 
пребарување, се креира посебна нитка која го прави пребарувањето, притоа, на секоја 
нитка ѝ се испраќа кој е зборот што треба да го пребарува и името на датотеката во која 
треба да го прави пребарувањето. Секоја нитка го пребарува зборот во својата датотека, 
и штом заврши, на екран го печати името на датотеката и колку пати се појавил зборот. 
Откако ќе завршат сите нитки, главната нитка на екран печати, за секоја датотека 
одделно, колку процентуално се појавил зборот во таа датотека (процент од вкупното 
појавување на зборот во сите датотеки). */
typedef struct{
    FILE *file;
    char filename[MAX_WORD];
    char search_word[MAX_WORD];
    int count;
}thread_arg;

void *prebaraj(void *arg){
    thread_arg data = *((thread_arg*)arg); 
    char line[BUFFER_SIZE]; //store each line we read from the file
    int word_count=0; //how many times the word is found
    int word_length= strlen(data.search_word); //length of the word we are searching

    // Read the file line by line
    while(fgets(line,BUFFER_SIZE,data.file)){
        // Pointer to track where the word is found in the line
        char *position=line;
        while((position=strstr(position,data.search_word))!=NULL){
            word_count++; // Increment count when the word is found
            position+=word_length; // Move the pointer past the found word
        }
    }
    data.count=word_count;
    fclose(data.file);
    pthread_exit(NULL);
}

int main(int argc,char* argv[]){
    char search_word[MAX_WORD];
    char filenames[MAX_WORD];
    int num_files;
    if (argc<2){
        printf("Vnesete zbor za prebaruvanje");
        scanf("%s",search_word);

        printf("Vnesete iminja na 3 datoteki");
        for(int i=0;i<3;i++){
            scanf("%s", filenames[i]);
        }
    } else {
        strcpy(search_word, argv[1]);
        num_files=argc-2;

        for(int i=0;i<num_files;i++){
            strcpy(filenames[i],argv[i+2]);
        }
    }

    FILE *files[MAX_FILES];
    for(int i=0;i<num_files;i++){
        files[i]=fopen(filenames[i],"r");
        if(!files[i]){
            printf("Ne moze da se otvori datotekata: %s\n", filenames[i]);
            exit(-1);
        }
    }
    
    thread_arg args[MAX_FILES];
    pthread_t nitki[MAX_FILES];
    int rc1;
    for(int i=0;i<num_files;i++){
        args[i].file=files[i];
        strcpy(args[i].filename, filenames[i]);
        strcpy(args[i].search_word, search_word);
        args[i].count=0;

        rc1=pthread_create(&nitki[i],NULL,prebaraj,(void *)&args[i]);
        if(rc1){
            printf("greska");
            exit(-1);
        }
    }

    for(int i=0;i<num_files;i++){
        pthread_join(nitki[i],NULL);
    }
    int total_count=0;
    for(int i=0;i<num_files;i++){
        printf("Datoteka:%s, Pojavuvanja %d\n",args[i].filename,args[i].count);
        total_count+= args[i].count;
    }
    
    printf("Vkupno pojavuvanja:%d\n",total_count);
    for(int i=0;i<num_files;i++){
        if(total_count>0){
            float percentage= (args[i].count / (float) total_count) *100;
            printf("Датотека: %s, Процент: %.2f%%\n", args[i].filename, percentage);
        }
    }

    return 0;
}