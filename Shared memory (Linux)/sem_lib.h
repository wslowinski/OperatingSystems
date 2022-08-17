#ifndef SEM_LIB_H
#define SEM_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

// #include "cap.h"
// #include "error.h"
// #include "random.h"

sem_t *SemMake(const char *name, int oflag, mode_t mode, unsigned int value);
sem_t *SemOpen(const char *name, int oflag);
int SemGetValue(sem_t *sem, int *s);
int SemPost(sem_t *sem);
int SemWait(sem_t *sem);
int SemClose(sem_t *sem);
int SemRemove(const char *name);

#endif