#include "producer.h"
#include "message.h"
#include "random.h"

#define NBYTE_PROD 5
#define N 100

void producer(int* filedes, char* input)
{ 
    char *buf;
    FILE *file;
    close(filedes[0]);
    
    
    buf = malloc(N);
    file = fopen(input, "r");

    if (file == NULL)
    {
        printf("Plik %s nie istnieje! Utworz najpierw plik!\n", input);
        exit(2);
    }

    while (file != NULL)
    {
        if (fgets (buf, NBYTE_PROD, file) == NULL)
        {
            perror("*** \033[1;95mKoniec pliku\033[0m ***\n");
            exit(2);
        }
        
        message(0, buf) ;
        
        if (write(filedes[1], buf, NBYTE_PROD) == -1)
        {
            perror("Write Error!\n");
            exit(EXIT_FAILURE);
        }
        
        sleep(Random(1, 5));
    }
    
    fclose(file) ;
    close(filedes[1]);
    free(buf);
    wait(NULL);
}
