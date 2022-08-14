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
    if (argc == 1)
    {
        message(argv[0]);
    }

    else if (argc == 2)
    {
        char *option = argv[1];
        message(argv[0]);
    }

    else if (argc >= 3)
    {
        int signal = 2;
        sscanf(argv[2], "%d", &signal);

        int pid = fork();

        switch(pid)
        {
            case -1:
                perror("Execl Error!\n");
                exit(1);
                break;

            case 0:
                execl("./3a.x", "3a.c", argv[1], argv[2], NULL);
                _exit(2);
                break;

            default:
                wait(0);
                printf("\n          >>>> \033[1;31mProces macierzysty\033[0m <<<< \n\n");
                sleep(1);
                my_signal_handler(signal);
                printf(" wyslano do procesu o identyfikatorze PID = %d\n", pid);
                kill(pid, signal);
                break;
        }
    }

    return 0;
}
