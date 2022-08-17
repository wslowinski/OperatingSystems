#include "lib.h"

sem_t *SemOpen(const char *name, int value)
{
    sem_open(name, O_CREAT, 0644, value);
    printf("Utworzony semafor o nazwie \033[1;31m%s\033[0m (%p)\nzainicjowano wartoscia = %d\n\n", name, &name, value);
}

int SemClose(sem_t *sem)
{
    sem_close(sem);
}

int SemGetValue(sem_t *sem, int *sval)
{
    sem_getvalue(sem, sval);
}

int SemPost(sem_t *sem)
{
    sem_post(sem);
}

int SemWait(sem_t *sem)
{
    sem_wait(sem);
}

int SemRemove(const char *name)
{
    sem_unlink(name);
    printf("Semafor o nazwie \033[1;31m%s\033[0m zostal usuniety.\n", name);
}