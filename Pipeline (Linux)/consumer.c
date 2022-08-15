#include "consumer.h"
#include "message.h"
#include "random.h"

#define NBYTE_CONS 6
#define N 100

void consumer(int* filedes, char* output) 
{
    char* buf;
    FILE* file;
    close(filedes[1]);
    
    buf = malloc(N);
    file = fopen(output, "w");

    while(read(filedes[0], buf, NBYTE_CONS) > 0)
    {
        message(1, buf);
        fputs(buf, file);
        sleep(Random(1, 5));
    }
    
    fclose(file);
    close(filedes[0]);
    free(buf);
}