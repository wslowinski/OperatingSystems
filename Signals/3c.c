#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>

#include "message.h"
#include "my_signal_handler.h"
 
int main(int argc, char *argv[])
{
	char *option = argv[1];
	int signal = atol(argv[2]);

    if (argc == 1)
    {
        message(argv[0]);
    }

    else if (argc == 2)
    {
        char *opt = argv[1];
        message(argv[0]);
    }

    else if (argc >= 3)
    {
        for(int i = 0; i < 3; i++)
        {
            switch(fork())
            {
                case -1:
                    perror("Execl Error!\n");
                    exit(1);
                    break;

                case 0:
                    setpgid(0, 0);
                    execl("./3a.x", "3a.c", argv[1], argv[2], NULL);
                    _exit(2);
                    break;

                default:
                    wait(NULL);
                    break;	
            }
        }

        sleep(1);
        printf("\n          >>>> \033[1;31mProces macierzysty\033[0m <<<< \n\n");
        
        sleep(1);
        my_signal_handler(signal);
        printf(" do grupy procesow o identyfikatorze PGID = %d\n", getpgrp());
        
        kill(getpgrp(), signal);
        return 0;
    }

	return 0;
}
