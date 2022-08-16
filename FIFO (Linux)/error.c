#include "error.h"

void Error(char *c)
{
    fprintf(stderr, "        *** \033[1;31mNiepoprawna liczba argumentow\033[0m ***\n\n");
    printf("Aby uruchomic program, nalezy podać parametry wywołaniatego tego\n");
    printf("programu w następujący sposob: \n");
    printf("%s [nazwa pliku inputowego] [nazwa pliku outputowego] [nazwa potoku]\n", c);
    printf("\nPrzyklad uzycia programu: \n");
    printf("%s input.txt output.txt FIFO\n", c);
    exit(1);
}