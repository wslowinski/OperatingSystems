#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>

int ShmOpen(const char *name, int flags, mode_t mode);
int FtRunCate(int fd, off_t length);
int ShmClose(int fd);
int ShmUnlink(const char *name);
void *MMap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int MunMap(void *addr, size_t length);

#endif