//procesi 0...1..2...argc-1
//nitki   0...1..2...argc-1
// falat #include ...

pid_t deca[100];
int vreme[100];
void *f(void *);
int main(int argc, char *argv[]){
    pthread_t nitki[100];
    int N=argc-1;
    int i;
    for (i=0;i<N;i++){
        deca[i]=fork();
        if(deca[i]==0){
            break;
        }
    }

    if(i<N){
        execlp(argv[i+1],argv[i+1],NULL);
    } else{
        int t[100];
        for(i=0;i<N;i++){
            t[i]=i;
            if(phread.create(nitki[i],null,f,(void *),&t[i])){ //??????????????
                return 0;
            }
        }
        for(i=0;i<N;i++) pthread_join(nitki[i],NULL);
    }
    for(i=0;i<N;i++){
        printf("%s ne trebashe %d vreme" argv[i+1],vreme[i]);
    }
    return 0;
}

void *f(void *t){
    int id=*((int *)t);
    int s=0;
    while(waitpid(deca[id],NULL,WNOHANG)!=deca[i]){
        sleep(1);
        s++;
    }
    vreme[i]=s;
    phread_exit(NULL);
}