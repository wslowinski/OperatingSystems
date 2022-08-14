#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cap.h"
#include "message.h"
#include "my_signal_handler.h"
#include "identifiers.h"

#define _XOPEN_SOURCE 500

int main(int argc, char **argv)
{
    cap(3);
    
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
        if ((strcmp(argv[1], "def") == 0) || (strcmp(argv[1], "ign") == 0) || (strcmp(argv[1], "sh") == 0))
        {
            char *option = argv[1];
            int signal_nr = atoi(argv[2]);
            if (strcmp (option, "def") == 0)
            {
                if (signal(signal_nr, SIG_DFL) == SIG_ERR)
                {
                    perror("Signal Error!\n");
                    exit(1);
                }
                else
                {
                    identifiers();
                    printf("Wykonano operacje domyslna!\n");
                }
                exit(EXIT_SUCCESS);
            }
            else if (strcmp (option, "ign") == 0)
            {
                if (signal(signal_nr, SIG_IGN) == SIG_ERR)
                {
                    perror("Signal Error!\n");
                    exit(1); 
                }
                identifiers();
            }
            else if (strcmp(option, "sh") == 0)
            {
                if (signal(signal_nr, my_signal_handler) != SIG_ERR)
                {
                    identifiers();
                    sleep(1);
                    my_signal_handler(signal_nr);
                    printf("\n");
                    exit(0);
                }
            }
        }
        else
        {
            printf("*** Argumenty nie sa poprawne! ***\n");
            printf("Wywolano funkcje pause().\n");
            printf("Czekam na polecenie kill z poziomu powloki.\n");
            pause();
        }
    }

    return 0;
}
