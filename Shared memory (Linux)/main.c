#include <stdio.h>
#include <signal.h>

#include "sem_lib.h"
#include "sharedmemory.h"

#define NELE 20
#define NBUF 5
#define N 256

#define PATH "./"
#define PROD_SEM "/PRODUCER_SEMAPHORE"
#define CONS_SEM "/CONSUMENT_SEMAPHORE"
#define SHARED_MEMORY_NAME "/SHARED_MEMORY"

sem_t *Sem_PROD;
sem_t *Sem_CONS;

int fdShMem;
char message[N];

typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
}SegmentPD;

static void SignalHandler(int sig)
{
    printf("[%s] SIGINT\n", message);
    sleep(1);
    exit(EXIT_SUCCESS);
}

void TheEnd(void)
{   
    SemClose(Sem_PROD);
    SemClose(Sem_CONS);
    SemRemove(PROD_SEM);
    SemRemove(CONS_SEM);
    printf("[%s] Semafory zostaly zamkniete i usuniete\n", message);
    
    ShmClose(fdShMem);
    ShmUnlink(SHARED_MEMORY_NAME);
    printf("[%s] Pamiec dzielona zostala zamknieta i usunieta\n", message);
    printf("\n---- \033[1;95mKoniec\033[0m ----\n");
    _exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    
    if (system("clear") == -1)
	{
		perror("Error in call to system() function");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < 60; i++) printf("=");
	printf("\nAutor: Vladyslav Slovinskyi                     Cwiczenie: 7\n");
	for(int i = 0; i < 60; i++) printf("=");
	printf("\n\n");

    sprintf(message, "\033[1;33m%s\033[0m", "MAIN");
    
    if(argc != 5)
    {
        fprintf(stderr, "        *** \033[1;31mNiepoprawna liczba argumentow\033[0m ***\n\n");
        printf("Aby uruchomic program, nalezy podac parametry wywolaniatego tego\n");
        printf("programu w następujący sposob: \n");
        printf("%s [Producent] [Konsument] [input.txt] [output.txt]\n", argv[0]);
        printf("\nPrzyklad uzycia programu: \n");
        printf("%s producers.x consumers.x in.txt out.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if(atexit(TheEnd) == -1)
    {
        perror("ATEXIT FUNCTION ERROR");
        _exit(EXIT_FAILURE);
    }

    if(signal(SIGINT, SignalHandler) == SIG_ERR)
    {
        perror("SIGNAL FUNCTION ERROR");
    }

    Sem_PROD = SemMake(PROD_SEM, O_EXCL|O_CREAT, 0644, NBUF);
    Sem_CONS = SemMake(CONS_SEM, O_EXCL|O_CREAT, 0644, 0);
    
    sleep(1);

    printf("[%s] Semafor Producenta\nAdres:              %p\nWartosc poczatkowa: %d\n\n", message, (void*)Sem_PROD, NBUF); 
    printf("[%s] Semafor Konsumenta\nAdres:              %p\nWartosc poczatkowa: %d\n\n", message, (void*)Sem_CONS, 0);

    fdShMem = ShmOpen(SHARED_MEMORY_NAME, O_EXCL|O_CREAT|O_TRUNC|O_RDWR, 0644); 
    FtRunCate(fdShMem, sizeof(SegmentPD));
    
    sleep(1);
    
    printf("[%s] Pamiec dzielona *** Adres: %d\nRozmiar: %ld\n", message, fdShMem, sizeof(SegmentPD));

    pid_t addresses[2];


    char Prod_Path_Name[N];
    char Cons_Path_Name[N];

    sprintf(Prod_Path_Name, "%s%s", PATH, argv[1]);
    sprintf(Cons_Path_Name, "%s%s", PATH, argv[2]);

    for(int i = 0; i < 2; i++)
    {
        switch(addresses[i] = fork())
        {
            case -1:
                perror("FORK FUNCTION ERROR");
                exit(EXIT_FAILURE);
                break;

            case 0:
                if(i == 0)
                {
                    execl(Prod_Path_Name, argv[1], PROD_SEM, argv[3], CONS_SEM, SHARED_MEMORY_NAME, NULL);
                    perror("EXECL FUNCTION ERROR");
                    _exit(EXIT_FAILURE);
                }

                else if(i == 1)
                {
                    execl(Cons_Path_Name, argv[2], CONS_SEM, argv[4], PROD_SEM, SHARED_MEMORY_NAME, NULL);
                    perror("EXECL FUNCTION ERROR");
                    _exit(EXIT_FAILURE);
                }
                break;
            
            default:
                break;     
        }
    }

    pid_t address = 0;

    for(int i = 0; i < 2; i++)
    {
        if((address = wait(NULL)) == -1)
        {
            perror("WAIT FUNCTION ERROR");
            _exit(EXIT_FAILURE);
        }

        if(address == addresses[0])
        {
            printf("\n[%s] Zakonczono proces \033[1;31mPRODUCENT\033[0m\n", message);
        }

        else
        {
            printf("\n[%s] Zakonczono Proces \033[1;36mCONSUMER\033[0m\n", message);
        }
    }
    
    return 0;
}