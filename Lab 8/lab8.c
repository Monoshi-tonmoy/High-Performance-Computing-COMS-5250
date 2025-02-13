#include <stdio.h>
#include <math.h>

// defining constants
#define TOLERANCE 1e-6  
#define E 2.718281828459

//Recurse factorial
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

// Exponential using taylor series
double exponential_taylor(double x) {
    int x0 = round(x);  
    double xr = x - x0; 
    
    // Compute e^x0 using pow()
    double exp_x0 = pow(E, x0);
    
    double result = 1.0;  // First term (n=0)
    double term = 1.0;    
    int n = 1;

    while (fabs(term) > TOLERANCE) {
        term *= xr / n;  
        result += term;
        n++;
    }
    
    return exp_x0 * result;  // e^x = e^x0 * e^xr
}

int main() {
    int n;
    double x;
    
    // Factorial computation
    printf("Enter an integer for factorial: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Factorial is undefined for negative numbers.\n");
    } else {
        printf("Factorial of %d is: %llu\n", n, factorial(n));
    }
    
    // Exponential computation
    printf("Enter a real number for exponential: ");
    scanf("%lf", &x);
    printf("Exponential of %.2f using Taylor Series is: %.4f\n", x, exponential_taylor(x));

    // Generate exp(x) values for x = 0, 0.02, ..., 1
    FILE *file = fopen("exp_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fprintf(file, "x,exp(x)\n"); //this works as a column header for our results
    for (double i = 0; i <= 1.02; i += 0.02) {
        fprintf(file, "%.2f,%.4f\n", i, exponential_taylor(i));
    }
    fclose(file);
    printf("exp(x) values saved to exp_data.txt\n");
    
    return 0;
}
