#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

#define TOL 1e-10  // Tolerance for convergence
#define MAX_ITERS 1000  // Maximum number of iterations

/**
 * Generates a random symmetric matrix of size n x n.
 *
 * @param n: Size of the matrix (n x n).
 * @return: A symmetric matrix with random values.
 */
matrix generate_random_symmetric_matrix(int n) {
    matrix A = new_matrix(n, n);
    srand((unsigned)time(NULL));  // Seed the random number generator
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            double val = (double)rand() / RAND_MAX;  // Random value between 0 and 1
            mget(A, i, j) = val;
            if (i != j) {
                mget(A, j, i) = val;  // Ensure symmetry
            }
        }
    }
    return A;
}

/**
 * Normalizes a vector by dividing each element by its Euclidean norm.
 *
 * @param v: Pointer to the vector to be normalized.
 */
void normalize_vector(vector* v) {
    double norm = sqrt(vector_dot_mult(v, v));  
    for (int i = 1; i <= v->size; i++) {
        vgetp(v, i) /= norm; 
    }
}

/**
 * Performs Power Iteration to approximate the largest eigenvalue and its corresponding eigenvector.
 *
 * @param A: Pointer to the input matrix.
 * @param eigenvalue: Pointer to store the computed eigenvalue.
 * @param eigenvector: Pointer to store the computed eigenvector.
 */
void power_iteration(const matrix* A, double* eigenvalue, vector* eigenvector) {
    int n = A->rows;
    vector v = new_vector(n);
    srand((unsigned)time(NULL));  // Seed the random number generator
    for (int i = 1; i <= n; i++) {
        vget(v, i) = (double)rand() / RAND_MAX;  // Random initial guess
    }
    normalize_vector(&v);  // Normalize the initial guess

    double lambda_old = 0.0;
    double lambda_new = 0.0;
    int iter = 0;

    while (iter < MAX_ITERS) {
        vector Av = matrix_vector_mult(A, &v);  // Compute A * v
        lambda_new = vector_dot_mult(&v, &Av);  // Rayleigh quotient

        if (fabs(lambda_new - lambda_old) < TOL) {  // Check for convergence
            break;
        }

        lambda_old = lambda_new;
        v = Av;  
        normalize_vector(&v);  
        iter++;
    }

    *eigenvalue = lambda_new;  
    *eigenvector = v;  
}

/**
 * Performs Inverse Iteration to approximate the eigenvalue closest to a given shift μ and its corresponding eigenvector.
 *
 * @param A: Pointer to the input matrix.
 * @param mu: Shift value (μ) for inverse iteration.
 * @param eigenvalue: Pointer to store the computed eigenvalue.
 * @param eigenvector: Pointer to store the computed eigenvector.
 */
void inverse_iteration(const matrix* A, double mu, double* eigenvalue, vector* eigenvector) {
    int n = A->rows;
    matrix A_muI = new_matrix(n, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mget(A_muI, i, j) = mgetp(A, i, j) - (i == j ? mu : 0.0);  // Compute A - μI
        }
    }

    vector v = new_vector(n);
    srand((unsigned)time(NULL));  // Seed the random number generator
    for (int i = 1; i <= n; i++) {
        vget(v, i) = (double)rand() / RAND_MAX;  // Random initial guess
    }
    normalize_vector(&v);  // Normalize the initial guess

    double lambda_old = 0.0;
    double lambda_new = 0.0;
    int iter = 0;

    while (iter < MAX_ITERS) {
        vector w = solve(&A_muI, &v);  // Solve (A - μI) * w = v
        normalize_vector(&w);  // Normalize the solution
        lambda_new = vector_dot_mult(&v, &w);  // Rayleigh quotient

        if (fabs(lambda_new - lambda_old) < TOL) {  // Check for convergence
            break;
        }

        lambda_old = lambda_new;
        v = w;  // Update eigenvector
        iter++;
    }

    *eigenvalue = mu + lambda_new; 
    *eigenvector = v;  
}
/**
 * Performs Rayleigh Quotient Iteration to approximate an eigenvalue and its corresponding eigenvector.
 *
 * @param A: Pointer to the input matrix.
 * @param eigenvalue: Pointer to store the computed eigenvalue.
 * @param eigenvector: Pointer to store the computed eigenvector.
 */
void rayleigh_quotient_iteration(const matrix* A, double* eigenvalue, vector* eigenvector) {
    int n = A->rows;
    vector v = new_vector(n);
    srand((unsigned)time(NULL));  // Seed the random number generator
    for (int i = 1; i <= n; i++) {
        vget(v, i) = (double)rand() / RAND_MAX;  // Random initial guess
    }
    normalize_vector(&v);  // Normalize the initial guess

    double lambda_old = 0.0;
    double lambda_new = 0.0;
    int iter = 0;

    while (iter < MAX_ITERS) {
        vector Av = matrix_vector_mult(A, &v);  // Compute A * v
        lambda_new = vector_dot_mult(&v, &Av);  // Rayleigh quotient

        if (fabs(lambda_new - lambda_old) < TOL) {  // Check for convergence
            break;
        }

        lambda_old = lambda_new;

        // Solve (A - λI) * w = v
        matrix A_lambdaI = new_matrix(n, n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                mget(A_lambdaI, i, j) = mgetp(A, i, j) - (i == j ? lambda_new : 0.0);  // Compute A - λI
            }
        }
        vector w = solve(&A_lambdaI, &v);  // Solve the linear system
        normalize_vector(&w);  // Normalize the solution
        v = w;  // Update eigenvector
        iter++;
    }

    *eigenvalue = lambda_new;  // Store the computed eigenvalue
    *eigenvector = v;  // Store the computed eigenvector
}

/**
 * Main function to demonstrate eigenvalue calculations using Power Iteration, Inverse Iteration, and Rayleigh Quotient Iteration.
 */
int main() {
    int n = 6;  // Size of the matrix
    matrix A = generate_random_symmetric_matrix(n);  // Generate a random symmetric matrix

    printf("Generated Symmetric Matrix A:\n");
    print_matrix_full(&A, "A");

    // Power Iteration
    double eigenvalue_power;
    vector eigenvector_power = new_vector(n);
    power_iteration(&A, &eigenvalue_power, &eigenvector_power);
    printf("\nPower Iteration:\n");
    printf("Eigenvalue: %lf\n", eigenvalue_power);
    printf("Eigenvector:\n");
    print_vector_full(&eigenvector_power, "v");

    // Inverse Iteration
    double mu = eigenvalue_power;  // Use the result from Power Iteration as the shift
    double eigenvalue_inverse;
    vector eigenvector_inverse = new_vector(n);
    inverse_iteration(&A, mu, &eigenvalue_inverse, &eigenvector_inverse);
    printf("\nInverse Iteration (mu = %lf):\n", mu);
    printf("Eigenvalue: %lf\n", eigenvalue_inverse);
    printf("Eigenvector:\n");
    print_vector_full(&eigenvector_inverse, "v");

    // Rayleigh Quotient Iteration
    double eigenvalue_rayleigh;
    vector eigenvector_rayleigh = new_vector(n);
    rayleigh_quotient_iteration(&A, &eigenvalue_rayleigh, &eigenvector_rayleigh);
    printf("\nRayleigh Quotient Iteration:\n");
    printf("Eigenvalue: %lf\n", eigenvalue_rayleigh);
    printf("Eigenvector:\n");
    print_vector_full(&eigenvector_rayleigh, "v");

    // Cleanup
    free(A.val);
    free(eigenvector_power.val);
    free(eigenvector_inverse.val);
    free(eigenvector_rayleigh.val);

    return 0;
}