#include "consumer.h"
#include "message.h"
#include "random.h"

#define NBYTE_CONS 4
#define N 100

void consumer(int filedesC, char* output) 
{
    char* buf;
    FILE* file;
    
    buf = malloc(N);
    file = fopen(output, "w");

    while(read(filedesC, buf, NBYTE_CONS) > 0)
    {
        message(1, buf);
        fputs(buf, file);
        sleep(Random(1, 5));
    }
    
    fclose(file);
    close(filedesC);
    free(buf);
}

int main(int argc, char **argv)
{
    int filedes;
	filedes = open(argv[2], O_RDONLY);
	consumer(filedes, argv[1]);
	return 0;
}
