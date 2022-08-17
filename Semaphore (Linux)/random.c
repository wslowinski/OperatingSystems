#include "random.h"
  
int Random(int lower, int upper)
{
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}