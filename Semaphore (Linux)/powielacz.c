#include "lib.h"

int main(int argc, char **argv)
{
    sem_t *semaphore = sem_open(argv[1], O_EXCL);
    int value;

    SemWait(semaphore); 

    printf("    PID = %d sekcja krytyczna\n", getpid());
    
    FILE *fp;
    if((fp = fopen("numer.txt", "r")) == NULL)
    {
        printf("Open Error!\n");
        exit(1);
    }

    int n;
    fscanf(fp, "%d", &n);

    printf("    PID = %d odczytano z pliku: \033[1;36m%d\033[0m\n", getpid(), n);
    
    if(fclose(fp) == -1)
    {
        printf ("Close Error!\n");
        exit(1);
    }

    sleep(Random(1, 4));
    
    n++;

    printf("    PID = %d zapisano do pliku: \033[1;36m%d\033[0m\n", getpid(), n);
    
    SemGetValue(semaphore, &value);
    
    printf("    Wartosc semafora = \033[1;36m%d\033[0m\n", value);

    FILE *f;
    if((f = fopen("numer.txt", "w")) == NULL)
    {
        printf ("Open Error!\n");
        exit(1);
    }

    fprintf(f, "%d", n);
    fclose(f);

    SemPost(semaphore);

    SemClose(semaphore);

    printf("Po sekcji krytycznej PID = %d \n", getpid());
    for(int i = 0; i < 40; i++) printf("-"); 
    printf("\n\n");   


    return 0;
}