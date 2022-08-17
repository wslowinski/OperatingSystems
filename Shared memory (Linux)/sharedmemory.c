#include "sharedmemory.h"

/*=================================================*/
int ShmOpen(const char *name, int flags, mode_t mode)
{
    int fd;
    if((fd = shm_open(name, flags, mode)) == -1)
    {
        perror("SHARED MEMORY OPEN ERROR");
        exit(EXIT_FAILURE);
    }
    return fd;
}
/*=================================================*/

int FtRunCate(int fd, off_t length)
{
    if(ftruncate(fd, length) == -1)
    {
        perror("FTRUNCATE FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return 0;
}
/*=================================================*/

int ShmClose(int fd)
{
    if(close(fd) == -1)
    {
        perror("CLOSE FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return 0;
}
/*=================================================*/

int ShmUnlink(const char *name)
{
    if(shm_unlink(name) == -1)
    {
        perror("SHARED MEMORY UNLINK ERROR");
        exit(EXIT_FAILURE);
    }
    return 0;
}
/*=================================================*/

void *MMap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    void *map;
    if((map = mmap(addr, length, prot, flags, fd, offset)) == MAP_FAILED)
    {
        perror("MAP FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return map;
}
/*=================================================*/

int MunMap(void *addr, size_t length)
{
    if(munmap(addr, length) == -1)
    {
        perror("MUNMAP FUNCTION ERROR");
        exit(EXIT_FAILURE);
    }
    return 0;
}
/*=================================================*/