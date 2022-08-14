#ifndef MY_SIGNAL_HANDLER_H
#define MY_SIGNAL_HANDLER_H

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void upcase(char *s);
void my_signal_handler(int signal);

#endif
