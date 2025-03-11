#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "matrix.h"
#include "trimatrix.h"

// Function to generate a lower triangular matrix L
matrix generate_L(int N) {
    matrix L = new_matrix(N, N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            mget(L, i, j) = (double)(i + j); // Example values
        }
    }
    return L;
}

// Function to compute A = LL^T
matrix compute_A(matrix* L) {
    int N = L->rows;
    matrix A = new_matrix(N, N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            double sum = 0.0;
            for (int k = 1; k <= N; k++) {
                sum += mgetp(L, i, k) * mgetp(L, j, k);
            }
            mget(A, i, j) = sum;
        }
    }
    return A;
}

int main() {
    int N = 6;

    // Generate L and A = LL^T
    matrix L = generate_L(N);
    matrix A = compute_A(&L);

    // Print matrix A
    printf("Matrix A (A = LL^T):\n");
    print_matrix(&A);

    // Phase 1: Convert A to Hessenberg form
    trimatrix T = new_trimatrix(N);
    Hessenberg(&A, &T);

    // Print Hessenberg matrix T
    printf("Hessenberg matrix T (Phase 1):\n");
    print_trimatrix(&T);

    // Phase 2: Apply QR algorithm to find eigenvalues
    QRA(&T);

    // Print eigenvalues (diagonal of T after QR algorithm)
    printf("Eigenvalues (Phase 2):\n");
    for (int i = 1; i <= N; i++) {
        printf("%13.6e\n", tget(&T, i, i));
    }

    // Clean up
    delete_matrix(&L);
    delete_matrix(&A);
    delete_trimatrix(&T);

    return 0;
}