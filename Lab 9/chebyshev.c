#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Functon to computer Chebyshev polynomial T_n(x)
double chebyshev(int n, double x) {
    switch (n) {
        case 0: return 1;
        case 1: return x;
        case 2: return 2*x*x - 1;
        case 3: return 4*x*x*x - 3*x;
        case 4: return 8*x*x*x*x - 8*x*x + 1;
        case 5: return 16*x*x*x*x*x - 20*x*x*x + 5*x;
        default: return 0;
    }
}

//Evaluate polynomial pN(x) using Chebyshev expansion
double evaluate_polynomial(int N, double x, double coefficients[]) {
    double sum = 0;
    for (int i = 0; i <= N; i++) {
        sum += coefficients[i] * chebyshev(i, x);
    }
    return sum;
}

int main() {
    int N = 5; // degree set in the question 
    double coefficients[6] = {1, -0.5, 0.75, -0.2, 0.3, -0.1}; // Example coefficients

    FILE *file = fopen("chebyshev_data.txt", "w");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    for (double x = -1; x <= 1; x += 0.05) {
        fprintf(file, "%lf %lf\n", x, evaluate_polynomial(N, x, coefficients));
    }
    
    fclose(file);

    // Calling python script using system
    system("python3 chebyshev.py");

    return 0;
}
