#include "message.h"

void message(int id, char* m)
{
    if (id == 0)
    {
        printf("*** \033[1;31mProducent\033[0m ***\n");
    }

    else if (id == 1)
    {
        printf("*** \033[1;36mKonsument\033[0m ***\n");
    }

    printf("%s\n", m) ;
}