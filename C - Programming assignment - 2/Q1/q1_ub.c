#include <stdio.h>
/* Undefined behaviour demo: count is modified twice without a sequence point */
int main(void)
{
    int count = 5;
    count = count++ + 1;   /* UNDEFINED BEHAVIOUR */
    printf("count = %d (unreliable)\n", count);
    return 0;
}
