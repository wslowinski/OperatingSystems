#include <stdio.h>
#include <string.h>

#include "sem_lib.h"
#include "sharedmemory.h"

#define NELE 20
#define NBUF 5
#define N 256

char message[N];

typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
}SegmentPD;

int main(int argc, char *argv[])
{
    sprintf(message, "\033[1;36m%s\033[0m", "CONSUMER");

    int fd;
    if((fd = open(argv[2], O_CREAT|O_TRUNC|O_WRONLY, 0777)) == -1)
    {
        perror("OPEN FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }

    sem_t *Sem_CONS = SemOpen(argv[1], O_RDWR);
    sem_t *Sem_PROD = SemOpen(argv[3], O_RDWR);

    sleep(1);

    int Sem_VPROD, Sem_VCONS;
    printf("\n[%s] Semafor Producenta \033[0;34m%s\033[0m\nAdres: %p\n", message, argv[3], (void*)Sem_PROD);
    printf("\n[%s] Semafor Konsumenta \033[0;34m%s\033[0m\nAdres: %p\n", message, argv[1], (void*)Sem_CONS);

    int fdShMem = ShmOpen(argv[4], O_RDWR, 0777);
    SegmentPD *Shared_Mem = (SegmentPD*)MMap(NULL, sizeof(SegmentPD), PROT_READ|PROT_WRITE, MAP_SHARED, fdShMem, 0);
    
    sleep(1);
    printf("\n[%s] Pamiec dzielona *** deskryptor: %d\n", message, fdShMem);    

    sleep(2);

    int Counter = 0;
    char tab[NELE];

    while(1)
    {
        SemWait(Sem_CONS);
        if(strcmp(Shared_Mem -> bufor[Shared_Mem -> wyjmij], ""))
        {
            strcpy(tab, Shared_Mem -> bufor[Shared_Mem -> wyjmij]);
            
            SemGetValue(Sem_CONS, &Sem_VCONS);
            SemGetValue(Sem_PROD, &Sem_VPROD);

            Shared_Mem -> wyjmij = (Shared_Mem -> wyjmij + 1) % NBUF;

            SemPost(Sem_PROD);

            Counter = write(fd, (char*)tab, strlen(tab));

            if(Counter == -1)
            {
                perror("WRITE FUNCTION ERROR");
                exit(EXIT_FAILURE);
            }

            printf("\n----------------------------------------------\n[%s] Semafor "
            "Producenta/Konsumeta: [%d/%d]\nBiezacy indeks: %d \nRozmiar tekstu: %d "
            "\nTekst:          %s\n----------------------------------------------\n", 
            message, Sem_VPROD, Sem_VCONS, Shared_Mem -> wyjmij, 
            Counter, tab);

            memset((char*)tab, 0, NELE);
        }

        else 
        {
            break;
        }
        
        sleep(2);
    }    

    if(close(fd) == -1)
    {
        perror("CLOSE FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }

    MunMap((void*)Shared_Mem, sizeof(SegmentPD));   
    ShmClose(fdShMem);
    SemClose(Sem_CONS);
    SemClose(Sem_PROD);
    return 0;
}