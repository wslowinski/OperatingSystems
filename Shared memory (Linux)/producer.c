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
    sprintf(message, "\033[1;31m%s\033[0m", "PRODUCER");

    int fd;
    if((fd = open(argv[2], O_RDONLY, 0644)) == -1)
    {
        perror("OPEN FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }

    sem_t *Sem_PROD = SemOpen(argv[1], O_RDWR);
    sem_t *Sem_CONS = SemOpen(argv[3], O_RDWR);

    int Sem_VPROD, Sem_VCONS;
    
    printf("\n[%s] Semafor Producenta \033[0;34m%s\033[0m\nAdres: %p\n", message, argv[1], (void*)Sem_PROD);
    printf("\n[%s] Semafor Konsumenta \033[0;34m%s\033[0m\nAdres: %p\n", message, argv[3], (void*)Sem_CONS);

    int fdShMem = ShmOpen(argv[4], O_RDWR, 0644);
    SegmentPD *Shared_Mem = (SegmentPD*)MMap(NULL, sizeof(SegmentPD), PROT_WRITE, MAP_SHARED, fdShMem, 0);
    printf("\n[%s] Pamiec dzielona *** deskryptor: %d\n", message, fdShMem);

    Shared_Mem -> wstaw = Shared_Mem -> wyjmij = 0; 

    int Counter = 0;
    char tab[NELE];
    tab[NELE - 1] = 0;

    while(1)
    {
        Counter = read(fd, (char*)tab, sizeof(char) * (NELE - 1));
        if(Counter == -1)
        {
            perror("READ FUNCTION ERROR");
            exit(EXIT_FAILURE);
        }

        SemWait(Sem_PROD);

        if(Counter == 0)
        {
            SemPost(Sem_CONS);    
            strcpy(Shared_Mem -> bufor[Shared_Mem -> wstaw], "");
            break;
        }

        strcpy(Shared_Mem -> bufor[Shared_Mem -> wstaw], tab);

        SemGetValue(Sem_CONS, &Sem_VCONS);
        SemGetValue(Sem_PROD, &Sem_VPROD);

        printf("\n----------------------------------------------\n[%s] Semafor " 
        "Producenta/Konsumeta: [%d/%d] \nBiezacy indeks: %d \nRozmiar tekstu: %d "
        "\nTekst:          %s\n----------------------------------------------\n", 
        message, Sem_VPROD, Sem_VCONS, Shared_Mem -> wstaw, Counter, 
        Shared_Mem -> bufor[Shared_Mem -> wstaw]);

        Shared_Mem -> wstaw = (Shared_Mem -> wstaw + 1) % NBUF;
        SemPost(Sem_CONS);
        
        sleep(2);
        
        memset((char*)tab, 0, NELE);
    }

    if(close(fd) == -1)
    {
        perror("CLOSE FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }

    MunMap((void*)Shared_Mem, sizeof(SegmentPD));  
    ShmClose(fdShMem);
    SemClose(Sem_PROD);
    SemClose(Sem_CONS);
    return 0;
}