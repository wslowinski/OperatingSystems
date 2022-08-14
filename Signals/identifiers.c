#include"identifiers.h"

void identifiers()
{
	printf("PID = %d PPID = %d PGID = %d\n", getpid(), getppid(), getpgrp());
}
