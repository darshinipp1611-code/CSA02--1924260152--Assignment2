#include <stdio.h>
/* Experiment: the 'return' of case 9 is removed -> fallthrough into case 8 */
char grade_bad(int marks)
{
    if (marks < 0 || marks > 100) return '?';
    char g = 'F';
    switch (marks / 10) {
        case 10:
        case 9: g = 'S';          /* missing break: falls through */
        case 8: g = 'A'; break;
        case 7: g = 'B'; break;
        case 6: g = 'C'; break;
        case 5: g = 'D'; break;
        default: g = 'F';
    }
    return g;
}
int main(void)
{
    int marks[] = {100, 95, 83, 50, 49, -5};
    for (int i = 0; i < 6; i++) printf("%d:%c ", marks[i], grade_bad(marks[i]));
    printf("\n");
    return 0;
}
