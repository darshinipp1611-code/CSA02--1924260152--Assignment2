#include <stdio.h>
/* Extra: bit counting, precedence trap, signed char trap */
static int count_on(unsigned char reg) { int c = 0; while (reg) { reg &= reg - 1; c++; } return c; }
int main(void)
{
    unsigned char reg = 0x0E; /* 00001110: FAN, AC, HEATER on */
    printf("reg=0x%02X devices ON = %d\n", reg, count_on(reg));
    int dev = 2;
    printf("reg & 1 << dev   = %d  (parsed as reg & (1<<dev): tests bit 2)\n", reg & 1 << dev);
    printf("(reg & 1) << dev = %d  (tests bit 0, then shifts result)\n", (reg & 1) << dev);
    signed char s = (signed char)0x80;      /* bit 7 set */
    printf("signed char 0x80 >> 7 = %d (sign extension, implementation-defined)\n", s >> 7);
    unsigned char u = 0x80;
    printf("unsigned char 0x80 >> 7 = %d\n", u >> 7);
    printf("signed char 0x80 == 0x80 ? %s (promoted to int -128)\n", s == 0x80 ? "yes" : "no");
    return 0;
}
