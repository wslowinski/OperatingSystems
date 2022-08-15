#include "cap.h"
#include "message.h"
#include "producer.h"
#include "consumer.h"
#include "error.h"

int main(int argc, char **argv)
{
	cap(4);

	if (argc == 1)
    {
        Error(argv[0]);
    }

	else if (argc == 2)
    {
        char *param = argv[1];
        Error(argv[0]);
    }

	else if (argc >= 3)
    {
		int filedes[2];
		
		if (pipe(filedes) == -1 )
		{
			perror("Pipe Error!\n");
			exit(EXIT_FAILURE);
		}
		
		switch(fork())
		{
			case -1:
				perror("fork() Error!\n");
				exit(EXIT_FAILURE) ;

			case 0:
				consumer(filedes, argv[2]);
				break;

			default:
				producer(filedes, argv[1]);
				break;
		}
	}

	return 0;
}
