#include <stdio.h>
#include <math.h>
/* Q6: micro-loan repayment schedule with guaranteed termination */
#define EPS   0.005   /* half a paisa: balance below this counts as repaid */
#define LIMIT 360     /* safety limit in months */

/* returns 0 = repaid, 1 = limit reached; print = show the schedule */
int simulate(double P, double r, double E, int print, int *months, double *total_int)
{
    double balance = P; int m = 0; *total_int = 0;
    if (print) printf("%-6s %-10s %-10s %-10s %-10s\n", "Month", "Opening", "Interest", "Repaid", "Closing");
    while (balance > EPS) {                  /* while: loan may already be zero */
        if (m == LIMIT) { *months = m; return 1; }   /* safety break */
        double open = balance;
        double interest = balance * r;
        balance += interest;
        double pay = (balance < E) ? balance : E;    /* last month: pay only what is left */
        balance -= pay;
        *total_int += interest;
        m++;
        if (print) printf("%-6d %-10.2f %-10.2f %-10.2f %-10.2f\n", m, open, interest, pay, balance < EPS ? 0.0 : balance);
    }
    *months = m; return 0;
}

int main(void)
{
    double P = 10000, r = 0.02; int m; double ti;
    printf("Loan Rs %.0f at %.0f%% per month, repayment Rs 2000\n", P, r * 100);
    simulate(P, r, 2000, 1, &m, &ti);
    printf("Months = %d, total interest = Rs %.2f, total paid = Rs %.2f\n\n", m, ti, P + ti);

    printf("Growth investigation (interest in month 1 = Rs %.0f):\n", P * r);
    printf("%-10s %-10s %-14s %-12s\n", "Repayment", "Months", "Formula n", "TotalInterest");
    double E[] = {2000, 1000, 500, 400, 300, 250, 220, 205, 201, 200.5, 200.1};
    for (int k = 0; k < 11; k++) {
        int st = simulate(P, r, E[k], 0, &m, &ti);
        double x = 1 - r * P / E[k];
        if (st) printf("%-10.1f %-10s %-14.2f %-12.2f\n", E[k], ">360 LIMIT", -log(x) / log(1 + r), ti);
        else    printf("%-10.1f %-10d %-14.2f %-12.2f\n", E[k], m, -log(x) / log(1 + r), ti);
    }

    printf("\nRepayment <= interest:\n");
    double bad[] = {200, 150};
    for (int k = 0; k < 2; k++) {
        int st = simulate(P, r, bad[k], 0, &m, &ti);
        printf("  E=%.0f -> %s after %d months\n", bad[k], st ? "LIMIT reached" : "repaid", m);
        if (st) printf("  Message: loan never clears; repayment must exceed monthly interest (Rs %.0f).\n", P * r);
    }

    printf("\nDanger of balance != 0 (repayment NOT clamped in last month):\n");
    double b = P;
    for (int k = 1; k <= 7; k++) {
        b = b * (1 + r); b -= 2000;   /* unclamped repayment */
        printf("  month %d balance = %.17g  (!= 0 is %s)\n", k, b, b != 0 ? "true" : "false");
    }
    double c = 0.1 * 3; printf("  0.1*3 == 0.3 ? %s\n", c == 0.3 ? "yes" : "no");
    return 0;
}
