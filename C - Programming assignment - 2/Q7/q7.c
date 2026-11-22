#include <stdio.h>
/* Q7: redesign of Q5 trial division. v1 = original, v2 = skip evens, v3 = 6k+-1 wheel */
static unsigned long d;

int v1(unsigned long n)
{ d = 0; if (n < 2) return 0;
  for (unsigned long i = 2; i * i <= n; i++) { d++; if (n % i == 0) return 0; }
  return 1; }

int v2(unsigned long n)                   /* test 2 once, then only odd divisors */
{ d = 0; if (n < 2) return 0; if (n < 4) return 1;
  d++; if (n % 2 == 0) return 0;
  for (unsigned long i = 3; i * i <= n; i += 2) { d++; if (n % i == 0) return 0; }
  return 1; }

int v3(unsigned long n)                   /* test 2 and 3, then only 6k-1 and 6k+1 */
{ d = 0; if (n < 2) return 0; if (n < 4) return 1;
  d++; if (n % 2 == 0) return 0;
  d++; if (n % 3 == 0) return 0;
  for (unsigned long i = 5; i * i <= n; i += 6) {
      d++; if (n % i == 0) return 0;
      d++; if (n % (i + 2) == 0) return 0;
  }
  return 1; }

int main(void)
{
    unsigned long t[] = {97, 100, 7919, 1000003, 999983, 1000000007UL};
    printf("%-11s %-9s | %-9s %-9s %-9s\n", "n", "result", "orig", "odd-only", "6k+-1");
    for (int k = 0; k < 6; k++) {
        int p = v1(t[k]); unsigned long a = d; v2(t[k]); unsigned long b = d; v3(t[k]); unsigned long c = d;
        printf("%-11lu %-9s | %-9lu %-9lu %-9lu\n", t[k], p ? "prime" : "not prime", a, b, c);
    }
    unsigned long A = 0, B = 0, C = 0; int bad = 0;
    for (unsigned long n = 0; n <= 100000; n++) {
        int r1 = v1(n); A += d; int r2 = v2(n); B += d; int r3 = v3(n); C += d;
        if (r1 != r2 || r1 != r3) bad++;
    }
    printf("\nAll n = 0..100000 : total divisions orig=%lu odd-only=%lu 6k+-1=%lu\n", A, B, C);
    printf("Ratio to original  : odd-only=%.3f  6k+-1=%.3f\n", (double)B / A, (double)C / A);
    printf("Disagreements between versions: %d\n", bad);
    A = B = C = 0;
    for (unsigned long n = 900001; n <= 1000003; n += 2) { v1(n); A += d; v2(n); B += d; v3(n); C += d; }
    printf("Odd n in 900001..1000003 : orig=%lu odd-only=%lu 6k+-1=%lu\n", A, B, C);
    return 0;
}
