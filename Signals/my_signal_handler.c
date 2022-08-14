#include "my_signal_handler.h"

void upcase(char *s)
{
    while (*s)
    {
        *s = toupper(*s);
        s++;        
    }
}

void my_signal_handler(int signal)
{
	char *str = strdup(sys_siglist[signal]);
	upcase(str);
    printf("Wyslano sygnal: %d) SIG%s", signal, str);
}
