#include <stdio.h>
#include <stdint.h>
/* Q5: all loop versions with division counts */
static unsigned long d;  /* divisions */

int prime_full_for(unsigned long n)      /* divisors 2..n-1 */
{ d = 0; if (n < 2) return 0;
  for (unsigned long i = 2; i < n; i++) { d++; if (n % i == 0) return 0; }
  return 1; }

int prime_sqrt_for(unsigned long n)      /* i*i <= n */
{ d = 0; if (n < 2) return 0;
  for (unsigned long i = 2; i * i <= n; i++) { d++; if (n % i == 0) return 0; }
  return 1; }

int prime_sqrt_while(unsigned long n)
{ d = 0; if (n < 2) return 0;
  unsigned long i = 2;
  while (i * i <= n) { d++; if (n % i == 0) return 0; i++; }
  return 1; }

int prime_sqrt_dowhile(unsigned long n)  /* guard needed: body runs before test */
{ d = 0; if (n < 2) return 0;
  if (n < 4) return 1;                   /* 2 and 3 are prime: 4 is the first i*i > ... */
  unsigned long i = 2;
  do { d++; if (n % i == 0) return 0; i++; } while (i * i <= n);
  return 1; }

int prime_dowhile_naive(unsigned long n) /* NO guard: wrong for 2 and 3 */
{ d = 0; if (n < 2) return 0;
  unsigned long i = 2;
  do { d++; if (n % i == 0) return 0; i++; } while (i * i <= n);
  return 1; }

int main(void)
{
    unsigned long t[] = {2, 3, 4, 97, 100, 7919, 1000003};
    printf("%-8s %-9s | %-11s %-9s %-9s %-9s\n", "n", "result", "i<n (for)", "sqrt for", "while", "do-while");
    for (int k = 0; k < 7; k++) {
        unsigned long n = t[k];
        int p = prime_sqrt_for(n); unsigned long a = d;
        prime_full_for(n);        unsigned long f = d;
        prime_sqrt_while(n);      unsigned long w = d;
        prime_sqrt_dowhile(n);    unsigned long dw = d;
        printf("%-8lu %-9s | %-11lu %-9lu %-9lu %-9lu\n", n, p ? "prime" : "not prime", f, a, w, dw);
    }
    printf("\nNaive do-while without guard:\n");
    for (int k = 0; k < 2; k++) printf("  n=%lu -> %s (should be prime)\n", t[k], prime_dowhile_naive(t[k]) ? "prime" : "NOT prime");

    printf("\nOverflow of i*i with 32-bit unsigned:\n");
    uint32_t i = 65536u;
    printf("  (uint32_t)65536 * 65536 = %u  -> test 'i*i <= n' is true for every n (wrong)\n", (uint32_t)(i * i));
    printf("  safe form 'i <= n / i' with n=4294967291: 65536 <= %u is %s\n", 4294967291u / 65536u, (65536u <= 4294967291u / 65536u) ? "true" : "false");

    /* Sieve alternative */
    enum { N = 1000003 };
    static unsigned char comp[N + 1];
    unsigned long marks = 0, primes = 0;
    for (unsigned long i2 = 2; i2 * i2 <= N; i2++)
        if (!comp[i2]) for (unsigned long j = i2 * i2; j <= N; j += i2) { comp[j] = 1; marks++; }
    for (unsigned long i2 = 2; i2 <= N; i2++) if (!comp[i2]) primes++;
    printf("\nSieve up to %d: %lu markings, %lu primes; 97:%d 100:%d 7919:%d 1000003:%d\n",
           N, marks, primes, !comp[97], !comp[100], !comp[7919], !comp[1000003]);
    return 0;
}
