#include "lib.h"

char *path;

void TheEnd (void)
{
    SemRemove(path);
    printf("\n---- \033[1;95mKoniec\033[0m ----\n");
}

int main(int argc, char **argv)
{
    cap(6);
    if (argc == 1)
    {
        Error(argv[0]);
    }

	else if (argc == 2)
    {
        char *param = argv[1];
        Error(argv[0]);
    }

	else if (argc >= 3)
    {
        int arg;
        sscanf(argv[2], "%d", &arg);

        system("touch numer.txt");
        FILE *file;
        if((file = fopen("numer.txt", "w")) == NULL)
        {
            printf ("Open Error!\n");
            exit(1);
        }
        fprintf(file, "%d", 0);
        fclose(file);

        sem_t *semaphore = SemOpen(argv[1], 1);



        for(int i = 0; i < arg; i++)
        {
            switch(fork())
            {
                case -1:
                    perror("fork error\n");
                    exit(1);
                    break;

                case 0:
                    for(int i = 0; i < 40; i++) printf("-");    
                    printf("\nPrzed sekcja krytyczna nr \033[1;36m%d\033[0m PID = %d\n", i + 1, getpid());
                    execl("./powielacz.x", "powielacz.c", argv[1], NULL);
                    break;
                
                default:
                    wait(0);
                    sleep(Random(1, 4));
                    break;
            }
        }

        FILE *f;
        if((f = fopen("numer.txt", "r")) == NULL)
        {
            printf("Open Error!\n");
            exit(1);
        }

        int n;
        fscanf(f, "%d", &n);

        for(int i = 0; i < 40; i++) printf("-");
        printf("\nIlosc sekcji krytycznych  = \033[1;36m%d\033[0m\n", arg);
        printf("Wartosc odczytana z pliku = \033[1;36m%d\033[0m\n\n", n);

        path = argv[1];
        
        if(atexit(TheEnd) != 0)
        {
            perror("Error in call to atexit() function");
            exit(EXIT_FAILURE);
        }

        return 0;
    }
}