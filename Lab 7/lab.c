#include <stdio.h>
#include <math.h>

#define TOLERANCE 1e-6  

// Function to compute factorial of an integer
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

// Function to compute exponential using Taylor Series expansion (just like we did it for python)
double exponential_taylor(double x) {
    double result = 1.0; 
    double term = 1.0;   
    int n = 1;

    // Keep adding terms until the change is smaller than tolerance
    while (fabs(term) > TOLERANCE) {
        term *= x / n;  // Calculate the next term: x^n / n!
        result += term; // Add the term to the result
        n++;
    }

    return result;
}

// Function to compute logarithm using Newton's Method (just like pyhton)
double logarithm_newton(double y) {
    if (y <= 0) {
        printf("Logarithm undefined for non-positive values.\n");
        return -1;  //error flag
    }

    double x = 1.0;  
    double e_x = exp(x);  // e^x for the first iteration

    while (fabs(e_x - y) > TOLERANCE) {
        x = x - (e_x - y) / e_x;  // Newton's method formula
        e_x = exp(x); // Update e^x at each step
    }

    return x;
}

int main() {
    int n;
    double x, y;

    // Input for factorial computation
    printf("Enter an integer for factorial: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Factorial is undefined for negative numbers.\n");
    } else {
        printf("Factorial of %d is: %llu\n", n, factorial(n));
    }

    // Input for exponential computation
    printf("Enter a real number for exponential: ");
    scanf("%lf", &x);
    printf("Exponential of %.2f using Taylor Series is: %.8f\n", x, exponential_taylor(x));

    // Input for logarithmic computation
    printf("Enter a real number for logarithm: ");
    scanf("%lf", &y);
    double log_result = logarithm_newton(y);
    if (log_result != -1) {
        printf("Logarithm of %.2f using Newton's Method is: %.8f\n", y, log_result);
    }

    return 0;
}