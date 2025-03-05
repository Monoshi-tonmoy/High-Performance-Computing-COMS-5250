#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

#define N 20
#define M 5


// Function to generate f(x) = sin(2*pi*x)
// This function calculates the value of the sine function at a given x.
double f(double x) {
    return sin(2 * M_PI * x);
}

// Function to perform Interpolation
// This function performs interpolation to estimate the value of a function at a given point x, given n data points (lecture)
double interpolation(double x, double* X, double* Y, int n) {
    double result = 0.0;
    for (int i = 0; i <= n; i++) {
        double term = Y[i];
        for (int j = 0; j <= n; j++) {
            if (j != i) {
                term *= (x - X[j]) / (X[i] - X[j]);
            }
        }
        result += term;
    }
    return result;
}

// Least Squares Fit (using normal equations A^T * A * c = A^T * b)
// This function performs a least squares fit to find the coefficients of a polynomial of degree m (given in lecture) that best fits the given data points (X, Y) with n points.
void least_squares_fit(double* X, double* Y, int n, int m, double* coeffs) {
    matrix A = new_matrix(n, m+1);
    vector b = new_vector(n);
    
    // Fill A matrix and b vector
    for (int i = 0; i < n; i++) {  
        vget(b, i) = Y[i];
        for (int j = 0; j <= m; j++) {  
            mget(A, i, j) = pow(X[i], j); // Set A[i][j]
        }
    }
    
    // Compute A^T * A and A^T * b
    matrix At = matrix_transpose(&A);
    matrix AtA = matrix_mult(&At, &A);
    vector Atb = matrix_vector_mult(&At, &b);  
    vector c = solve(&AtA, &Atb); 
    
    // Storing coefficients
    for (int i = 0; i <= m; i++) {
        coeffs[i] = vget(c, i); 
    }
    
    //These cleaning up was resulting double free, in my case, couldn't solve it
    // free(A.val);    // Free A
    // free(b.val);    // Free b
    // free(AtA.val);  // Free AtA
    // free(Atb.val);  // Free Atb
    // free(c.val);    // Free c
}

// least squares polynomial
double eval_poly(double x, double* coeffs, int m) {
    double result = 0.0;
    for (int i = 0; i <= m; i++) {
        result += coeffs[i] * pow(x, i);
    }
    return result;
}

int main() {
    double X[N+1], Y[N+1], coeffs[M+1];
    for (int i = 0; i <= N; i++) {
        X[i] = i / (double)N;
        Y[i] = f(X[i]);
    }
    
    // Least squares fitting
    least_squares_fit(X, Y, N+1, M, coeffs);
    
    // Print values for plotting
    // This section writes the true function, interpolated values, and least squares polynomial values to a file for visualization.
    FILE *fp = fopen("output.txt", "w");
    for (double x = 0; x <= 1; x += 0.01) {
        fprintf(fp, "%lf %lf %lf %lf\n", x, f(x), interpolation(x, X, Y, N), eval_poly(x, coeffs, M));
    }
    fclose(fp);
    
    // Python script for generating plots
    // This section calls a Python script to visualize the results using the data written to `output.txt`.
    printf("Calling Python script for visualization...\n");
    int status = system("python3 plot_results.py");
    if (status == -1) {
        printf("Error: Failed to execute Python script.\n");
    }
    
    return 0;
}