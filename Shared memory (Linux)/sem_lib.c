#include "sem_lib.h"

/*=================================================*/
sem_t *SemMake(const char *name, int oflag, mode_t mode, unsigned int value)
{
    sem_t *addr;
    if((addr = sem_open(name, oflag, mode, value)) == SEM_FAILED)
    {
        perror("SEMAPHORE MAKE FUNCTION ERROR");
        _exit(EXIT_FAILURE);
    }
    return addr;
}
/*=================================================*/

sem_t *SemOpen(const char *name, int oflag)
{
    sem_t *addr;
    if((addr = sem_open(name, oflag)) == SEM_FAILED)
    {
        perror("SEMAPHORE OPEN FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return addr;
}
/*=================================================*/

int SemClose(sem_t *sem)
{
    if(sem_close(sem) == -1)
    {
        perror("SEMAPHORE CLOSE FUNCTION ERROR");
        exit(EXIT_FAILURE);  
    }
    return 0;
}
/*=================================================*/

int SemGetValue(sem_t *sem, int *sval)
{
    if(sem_getvalue(sem, sval) == -1)
    {
        perror("SEMAPHORE GET VALUE FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return 0;
}
/*=================================================*/

int SemPost(sem_t *sem)
{
    if(sem_post(sem) == -1)
    {
        perror("SEMAPHORE POST FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return 0;
}
/*=================================================*/

int SemWait(sem_t *sem)
{
    if(sem_wait(sem) == -1)
    {
        perror("SEMAPHORE WAIT FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return 0;
}
/*=================================================*/

int SemRemove(const char *name)
{
    if(sem_unlink(name) == -1)
    {
        perror("SEMAPHORE UNLINK FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return 0;
}
/*=================================================*/