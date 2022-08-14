#include "message.h"

void message(char *c)
{
    fprintf(stderr, "        *** \033[1;31mNiepoprawna liczba argumentow\033[0m ***\n");
    printf("Aby uruchomic program, nalezy podać parametry wywołaniatego tego\n");
    printf("programu w następujący sposob: \n");
    printf("%s [ustawienie obslugi sygnalu] [nr sygnalu]\n", c);
    printf("gdzie:\n \tdef - operacja domyslna (default)\n \tign - ignorowanie\n \tsh - przechwycenie (signal handling)\n");
    printf("\nPrzyklad uzycia programu z opcja przechwycenia sygnalu SIGINT: \n");
    printf("%s sh 2\n", c);
    exit(1);
}
