#include <stdio.h>
/* Q2: short-circuit evaluation experiments, 1000 sample passengers */
static long calls = 0, audit = 0;
static int slow_verify(int id)      { calls++; return id % 20 == 0; }          /* disability card: 5% */
static int slow_verify_log(int id)  { calls++; audit++; return id % 20 == 0; } /* also writes audit log */
static int is_senior(int id)        { return id % 10 < 3; }                    /* 30% */
static int class_ok(int id)         { return id % 4 != 0; }                    /* 75% */

int main(void)
{
    const int N = 1000;
    long granted;

    /* Part 1: when is the second operand skipped? */
    int a = 0, b = 0;
    if (0 && (a = 1)) {}   if (1 || (b = 1)) {}
    printf("(0 && (a=1)): a=%d (not evaluated)\n(1 || (b=1)): b=%d (not evaluated)\n", a, b);
    int x = 0, y = 0;
    if (0 & (x = 1)) {}    if (1 | (y = 1)) {}
    printf("(0 &  (x=1)): x=%d (evaluated)\n(1 |  (y=1)): y=%d (evaluated)\n\n", x, y);

    printf("%-42s %8s %8s\n", "Condition order", "Calls", "Granted");
    /* A: slow check first, short-circuit */
    calls = granted = 0;
    for (int i = 0; i < N; i++) granted += (slow_verify(i) || (is_senior(i) && class_ok(i)));
    printf("%-42s %8ld %8ld\n", "A: slow || (senior && class)", calls, granted);
    /* B: cheap first, short-circuit */
    calls = granted = 0;
    for (int i = 0; i < N; i++) granted += ((is_senior(i) && class_ok(i)) || slow_verify(i));
    printf("%-42s %8ld %8ld\n", "B: (senior && class) || slow", calls, granted);
    /* C: nested if */
    calls = granted = 0;
    for (int i = 0; i < N; i++) {
        if (is_senior(i)) { if (class_ok(i)) { granted++; continue; } }
        if (slow_verify(i)) granted++;
    }
    printf("%-42s %8ld %8ld\n", "C: nested if (same logic as B)", calls, granted);
    /* D: non-short-circuit | and & */
    calls = granted = 0;
    for (int i = 0; i < N; i++) granted += ((is_senior(i) & class_ok(i)) | slow_verify(i));
    printf("%-42s %8ld %8ld\n", "D: (senior & class) | slow", calls, granted);

    /* Changed condition: verification also writes an audit log */
    calls = audit = granted = 0;
    for (int i = 0; i < N; i++) granted += ((is_senior(i) && class_ok(i)) || slow_verify_log(i));
    printf("\nAudit, short-circuit B : calls=%ld audit entries=%ld (of %d passengers) granted=%ld\n", calls, audit, N, granted);
    calls = audit = granted = 0;
    for (int i = 0; i < N; i++) { int v = slow_verify_log(i); granted += (v || (is_senior(i) && class_ok(i))); }
    printf("Audit, verify every one : calls=%ld audit entries=%ld (of %d passengers) granted=%ld\n", calls, audit, N, granted);
    return 0;
}
