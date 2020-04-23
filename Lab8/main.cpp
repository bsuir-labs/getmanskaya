#include <math.h>
#include <stdio.h>

double Newton(double a, double b, double eps);
double f(double x);
double df(double x);

double safeReadDouble(const char *prompt);

int main()
{
    printf("Variant 2.\n");
    printf("Function: x^2-10*sin(x)^2+2\n");
    printf("Newton method.\n\n");

    double a = safeReadDouble("Specify range start value: ");
    double b = safeReadDouble("Specify range end value: ");
    double eps = safeReadDouble("Specify epsilon: ");
    double h = safeReadDouble("Specify step: ");

    int rootcnt = 0;
    for (double x = a; x <= b; x += h)
    {
        if (f(x) * f(x + h) < 0)
        {
            double root = Newton(x, x + h, eps);
            printf("Root #%d: %lf\n", ++rootcnt, root);
        }
    }

    if (!rootcnt)
        printf("No roots found in the range [%lf; %lf]\n", a, b);
    return 0;
}

double Newton(double a, double b, double eps)
{
    double x1 = (a + b) / 2, delta = 0, x2;
    do {
        x2 = x1 - f(x1) / df(x1);
        delta = fabs(x2 - x1);
        x1 = x2;
    } while (delta > eps);
    return x2;
}

double f(double x)
{
    return x * x - 10 * sin(x) * sin(x) + 2;
}

double df(double x)
{
    return 2 * (x - 10 * sin(x) * cos(x));
}

double safeReadDouble(const char *prompt)
{
    bool ok = false;
    double res;
    do {
        printf("%s", prompt);
        ok = scanf("%lf", &res) == 1;
        char c;
        while ((c = getc(stdin)) != '\n' && c != EOF);
        if (!ok)
            printf("Error, try once again\n");
    } while (!ok);
    return res;
}
