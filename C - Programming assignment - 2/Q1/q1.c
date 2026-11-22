#include <stdio.h>
/* Q1: Jan Aushadhi billing - buggy single expression vs corrected version */
int main(void)
{
    int price[3] = {100, 250, 999};
    int qty[3]   = {5, 2, 3};
    int senior[3]= {1, 0, 1};
    printf("%-5s %-6s %-4s %-3s | %-10s %-8s | %-10s %-8s\n",
           "Bill","Price","Qty","Sr","BuggyTotal","BuggyNet","FixedTotal","FixedNet");
    for (int i = 0; i < 3; i++) {
        int p = price[i], q = qty[i], s = senior[i];
        /* original (buggy) expression, integer arithmetic */
        int total = p * q - p * q * 15 / 100 * s + p * q * 5 / 100;
        int net = total > 1000 ? total - 50 : total;
        /* corrected: intermediate variables, double, GST on discounted amount */
        double gross    = (double)p * q;
        double discount = s ? gross * 0.15 : 0.0;
        double taxable  = gross - discount;
        double gst      = taxable * 0.05;
        double ftotal   = taxable + gst;
        double fnet     = ftotal > 1000 ? ftotal - 50 : ftotal;
        printf("%-5d %-6d %-4d %-3d | %-10d %-8d | %-10.2f %-8.2f\n",
               i + 1, p, q, s, total, net, ftotal, fnet);
    }
    return 0;
}
