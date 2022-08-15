#include "cap.h"

void cap(int ex_numb)
{   
	if (system("clear") == -1)
	{
		perror("Error in call to system() function");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < 60; i++) printf("=");
	printf("\nAutor: Vladyslav Slovinskyi                     Cwiczenie: %d\n", ex_numb);
	for(int i = 0; i < 60; i++) printf("=");
	printf("\n\n");
}
