/* Да се напише програма во C која работи со процеси и нитки. Главната програма (главната нитка) како
 аргумент добива име на влезна датотека. Главната нитка треба да креира онолку нитки колку што треба,
 така што, секоја нитка да добие по 10 линии од влезната датотека (нема повеќе од 1000 линии, а притоа
 последната нитка може да добие и помалку од 10 линии). Секоја една од нитките, ги изминува своите 10
 линии од датотеката и брои колку има големи а колку мали букви. Откако ќе завршат нитките, главната
 нитка печати на екран колку секоја нитка нашла големи и мали букви и печати колку вкупно големи и
 мали букви биле пронајдени. Не е дозволено содржината на целата датотека да биде прочитана во низа
 т.е. секоја од нитките мора да работи со FILE * покажувач за изминување на датотеката т.е. на линиите
 од датотеката.  */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

#define MAX_FILENAME 256
#define MAX_LINES 1000
#define LINES_PER_THREAD 10

// Struktura za podatoci na sekoja nitka
typedef struct {
    int thread_id;
    FILE *file;
    int start_line;
    int lines_to_read;
    int uppercase_count;
    int lowercase_count;
} ThreadData;

// Mutex za sinhronizacija na pecatenje
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

// Vkupni brojaci
int total_uppercase = 0;
int total_lowercase = 0;

// Funkcija za nitka koja broi bukvi
void *count_letters(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    char line[1024];
    int local_uppercase = 0;
    int local_lowercase = 0;
    int lines_read = 0;

    // Postavi pozicija na datotekata na pocetnata linija
    fseek(data->file, 0, SEEK_SET);
    
    // Прескокни линии до почетната линија
    for (int i = 0; i < data->start_line; i++) {
        if (fgets(line, sizeof(line), data->file) == NULL) {
            break;
        }
    }

    // Читај линии за оваа нитка
    while (lines_read < data->lines_to_read && 
           fgets(line, sizeof(line), data->file) != NULL) {
        
        // Брои големи и мали букви во секоја линија
        for (int i = 0; line[i] != '\0'; i++) {
            if (isupper(line[i])) {
                local_uppercase++;
            } else if (islower(line[i])) {
                local_lowercase++;
            }
        }
        
        lines_read++;
    }

    // Зачувај локалните броеви во структурата
    data->uppercase_count = local_uppercase;
    data->lowercase_count = local_lowercase;

    // Синхронизирано додавање на вкупните броеви
    pthread_mutex_lock(&print_mutex);
    total_uppercase += local_uppercase;
    total_lowercase += local_lowercase;
    
    // Печати резултат за оваа нитка
    printf("Nитка %d: Големи букви = %d, Мали букви = %d\n", 
           data->thread_id, local_uppercase, local_lowercase);
    pthread_mutex_unlock(&print_mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    // Провери дали е даден влезен фајл
    if (argc != 2) {
        fprintf(stderr, "Употреба: %s <влезна_датотека>\n", argv[0]);
        return 1;
    }

    // Отвори датотека
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Грешка при отворање на датотека");
        return 1;
    }

    // Пресметај број на линии во датотека
    int total_lines = 0;
    char temp_line[1024];
    while (fgets(temp_line, sizeof(temp_line), file) != NULL) {
        total_lines++;
    }
    rewind(file);  // Врати покажувач на почеток на датотека

    // Пресметај број на нитки потребни
    int num_threads = (total_lines + LINES_PER_THREAD - 1) / LINES_PER_THREAD;

    // Создај низа за нитки и нивни податоци
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    ThreadData *thread_data = malloc(num_threads * sizeof(ThreadData));

    // Создавање на нитки
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].file = file;
        thread_data[i].start_line = i * LINES_PER_THREAD;
        
        // Пресметај колку линии ќе чита оваа нитка
        if (i == num_threads - 1) {
            // Последна нитка може да чита помалку од 10 линии
            thread_data[i].lines_to_read = total_lines - (i * LINES_PER_THREAD);
        } else {
            thread_data[i].lines_to_read = LINES_PER_THREAD;
        }

        // Создади нитка
        if (pthread_create(&threads[i], NULL, count_letters, &thread_data[i]) != 0) {
            perror("Грешка при создавање нитка");
            return 1;
        }
    }

    // Чекај сите нитки да завршат
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Печати вкупни резултати
    printf("\nВкупно: Големи букви = %d, Мали букви = %d\n", 
           total_uppercase, total_lowercase);

    // Ослободи ресурси
    fclose(file);
    free(threads);
    free(thread_data);

    return 0;
}