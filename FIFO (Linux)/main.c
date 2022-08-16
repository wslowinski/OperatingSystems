#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "cap.h"
#include "message.h"
#include "error.h"

int main(int argc, char **argv)
{
	cap(5);

	if (argc == 1)
    {
        Error(argv[0]);
    }

	else if (argc == 2)
    {
        char *param = argv[1];
        Error(argv[0]);
    }

	else if (argc == 3)
    {
        char *param1 = argv[1];
		char *param2 = argv[2];
        Error(argv[0]);
    }

	else if (argc >= 4)
    {		
		if (mkfifo(argv[3], 0644) == -1 )
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
				execl("./consumer.x", "consumer.c", argv[2], argv[3], NULL);
				break;

			default:
				execl("./producer.x", "producer.c", argv[1], argv[3], NULL);
				break;
		}
		
		if (unlink(argv[3]) == -1 )
		{
			perror("Unlink Error!\n");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}
