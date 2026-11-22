#include <stdio.h>
/* Grade rules: 90-100 S, 80-89 A, 70-79 B, 60-69 C, 50-59 D, below 50 F, invalid '?' */
char grade_ladder(int m)
{
    if (m < 0 || m > 100) return '?';
    else if (m >= 90) return 'S';
    else if (m >= 80) return 'A';
    else if (m >= 70) return 'B';
    else if (m >= 60) return 'C';
    else if (m >= 50) return 'D';
    else return 'F';
}
char grade(int marks)
{
    if (marks < 0 || marks > 100) return '?';
    switch (marks / 10) {              /* TODO 1: switch with combined cases */
        case 10: case 9: return 'S';
        case 8: return 'A';
        case 7: return 'B';
        case 6: return 'C';
        case 5: return 'D';
        default: return 'F';           /* 0..4 */
    }
}
char grade_table(int m)
{
    static const char g[11] = {'F','F','F','F','F','D','C','B','A','S','S'};
    return (m < 0 || m > 100) ? '?' : g[m / 10];
}
int main(void)
{
    int marks[] = {100, 95, 83, 50, 49, -5};
    for (int i = 0; i < 6; i++) printf("%d:%c ", marks[i], grade(marks[i]));
    printf("\n\nBoundary test set (ladder / switch / table):\n");
    int t[] = {-1, 0, 49, 50, 59, 60, 69, 70, 79, 80, 89, 90, 99, 100, 101};
    int bad = 0;
    for (int i = 0; i < 15; i++) {
        char a = grade_ladder(t[i]), b = grade(t[i]), c = grade_table(t[i]);
        printf("%4d : %c %c %c %s\n", t[i], a, b, c, (a == b && b == c) ? "" : "MISMATCH");
        if (!(a == b && b == c)) bad++;
    }
    printf("Mismatches: %d\n", bad);
    return 0;
}
