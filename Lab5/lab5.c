#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 1024

void command1(const char *pipe1) {
    FILE *fp = fopen(pipe1, "w");
    if (fp == NULL) {
        perror("Error opening pipe1.txt");
        exit(1);
    }

    char buffer[MAX_LENGTH];
    printf("Внесете текст (Enter '\\0' за крај):\n");

    while (1) {
        if (fgets(buffer, MAX_LENGTH, stdin) == NULL) {
            break;
        }

        // Проверка за нул терминатор
        if (strcmp(buffer, "\\0\n") == 0) {
            break;
        }

        // Запишување во pipe1.txt
        fputs(buffer, fp);
    }

    fclose(fp);
}

void command2(const char *pipe1, const char *pipe2) {
    // Отворање на двата pipe фајла
    FILE *fp1 = fopen(pipe1, "r");
    FILE *fp2 = fopen(pipe2, "w");

    if (fp1 == NULL || fp2 == NULL) {
        perror("Error opening files");
        exit(1);
    }

    char buffer[MAX_LENGTH];

    // Читање од pipe1 и запишување во pipe2
    while (fgets(buffer, MAX_LENGTH, fp1) != NULL) {
        fputs(buffer, fp2);
    }

    fclose(fp1);
    fclose(fp2);
}

void command3(const char *pipe2) {
    FILE *fp = fopen(pipe2, "r");
    if (fp == NULL) {
        perror("Error opening pipe2.txt");
        exit(1);
    }

    char buffer[MAX_LENGTH];
    int spaceCount = 0;

    // Читање од pipe2 и броење празни места
    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == ' ') {
                spaceCount++;
            }
        }
        // Печатење на прочитаниот текст
        printf("%s", buffer);
    }

    printf("\nБрој на празни места: %d\n", spaceCount);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Употреба: %s <команда_број>\n", argv[0]);
        return 1;
    }

    const char *pipe1 = "pipe1.txt";
    const char *pipe2 = "pipe2.txt";
    int command_num = atoi(argv[1]);

    switch (command_num) {
        case 1:
            command1(pipe1);
            break;
        case 2:
            command2(pipe1, pipe2);
            break;
        case 3:
            command3(pipe2);
            break;
        default:
            printf("Невалидна команда. Користете 1, 2 или 3.\n");
            return 1;
    }

    return 0;
}