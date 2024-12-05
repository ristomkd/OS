// Ги вклучуваме потребните библиотеки
#include <stdio.h>      // За основни влез/излез операции
#include <stdlib.h>     // За rand() и exit()
#include <string.h>     // За работа со стрингови
#include <unistd.h>     // За sleep()
#include <sys/ipc.h>    // За IPC (Inter-Process Communication)
#include <sys/shm.h>    // За работа со shared memory
#include <sys/types.h>  // За дефинирање на различни типови
#include <time.h>       // За иницијализација на random seed

// Дефинираме големина на меморијата
#define GOLEMINA 1024
#define GOLEMINA_PORAKA (GOLEMINA - 1)

// Структура за споделената меморија
struct zaednichka_memorija {
    char ima_poraka;              // 1 = има порака, 0 = нема порака
    char poraka[GOLEMINA_PORAKA]; // Местото за пораката
};

// Функција за првиот процес - чита од тастатура и запишува во меморија
void proces_1(int id_memorija) {
    // Се поврзуваме со заедничката меморија
    struct zaednichka_memorija *mem = (struct zaednichka_memorija *)shmat(id_memorija, NULL, 0);
    if (mem == (void *)-1) {
        printf("Грешка при поврзување со меморијата\n");
        exit(1);
    }

    char tekst[GOLEMINA_PORAKA];
    while(1) {
        // Читаме порака од тастатура
        printf("Внесете порака: ");
        fgets(tekst, GOLEMINA_PORAKA, stdin);
        tekst[strcspn(tekst, "\n")] = 0;  // Го бришеме new line карактерот

        // Ја запишуваме во меморијата
        mem->ima_poraka = 1;
        strcpy(mem->poraka, tekst);
        
        // Спиеме случаен број секунди (1-10)
        int vreme_spienie = rand() % 10 + 1;
        printf("Процес 1: Спијам %d секунди\n", vreme_spienie);
        sleep(vreme_spienie);

        // Проверуваме дали пораката е избришана
        while(mem->ima_poraka == 1) {
            printf("Процес 1: Чекам пораката да биде избришана...\n");
            sleep(1);
        }
    }
}

// Функција за вториот процес - брише пораки на секои 5 секунди
void proces_2(int id_memorija) {
    struct zaednichka_memorija *mem = (struct zaednichka_memorija *)shmat(id_memorija, NULL, 0);
    if (mem == (void *)-1) {
        printf("Грешка при поврзување со меморијата\n");
        exit(1);
    }

    while(1) {
        sleep(5);  // Спиеме 5 секунди
        
        // Ја бришеме пораката ако постои
        if(mem->ima_poraka == 1) {
            memset(mem->poraka, 0, GOLEMINA_PORAKA); // Пополнуваме со нули
            mem->ima_poraka = 0;
            printf("Процес 2: Пораката е избришана\n");
        }
    }
}

// Функција за третиот процес - чита од меморија и печати
void proces_3(int id_memorija) {
    struct zaednichka_memorija *mem = (struct zaednichka_memorija *)shmat(id_memorija, NULL, 0);
    if (mem == (void *)-1) {
        printf("Грешка при поврзување со меморијата\n");
        exit(1);
    }

    while(1) {
        // Проверуваме дали има порака
        if(mem->ima_poraka == 1) {
            printf("Процес 3: Прочитана порака: %s\n", mem->poraka);
            
            // Спиеме случаен број секунди
            int vreme_spienie = rand() % 10 + 1;
            printf("Процес 3: Спијам %d секунди\n", vreme_spienie);
            sleep(vreme_spienie);
        }
        sleep(1);  // Проверуваме на секоја секунда
    }
}

int main(int argc, char *argv[]) {
    // Проверка на аргументите
    if(argc != 3) {
        printf("Користење: %s <тип_на_процес> <клуч>\n", argv[0]);
        printf("тип_на_процес може да биде 1, 2 или 3\n");
        return 1;
    }

    // Ги земаме аргументите
    int tip_proces = atoi(argv[1]);
    key_t kluch = atoi(argv[2]);

    // Креираме или земаме пристап до заедничката меморија
    int id_memorija = shmget(kluch, sizeof(struct zaednichka_memorija), IPC_CREAT | 0666);
    if(id_memorija == -1) {
        printf("Грешка при креирање на меморијата\n");
        return 1;
    }

    // Иницијализираме random seed
    srand(time(NULL));

    // Стартуваме соодветен процес според аргументот
    switch(tip_proces) {
        case 1:
            proces_1(id_memorija);
            break;
        case 2:
            proces_2(id_memorija);
            break;
        case 3:
            proces_3(id_memorija);
            break;
        default:
            printf("Невалиден тип на процес. Користете 1, 2 или 3.\n");
            return 1;
    }

    return 0;
}