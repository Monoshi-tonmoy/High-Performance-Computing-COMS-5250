#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "trimatrix.h"

// Function prototypes
void Hessenberg(const matrix* Ain, trimatrix* T); 
void QRA(trimatrix* T);

int main() {
    // Step 1: Define matrix size N = 6
    const int N = 6;

    // Step 2: Generate a random symmetric positive definite matrix A = L * L^T
    matrix L = new_matrix(N, N);
    matrix A = new_matrix(N, N);

    // Fill L with random values
    int seed = 39;
    srand(seed);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {  // Only fill lower triangle
            mget(L, i, j) = ((i * j + seed) % 10 + 1);  
        }
    }

    // Compute A = L * L^T
    A = matrix_mult(&L, &L);

    // Print the original matrix A
    printf("Original Matrix A (6x6):\n");
    print_matrix(&A);  

    // Step 3: Convert A to Tridiagonal Form (Phase 1)
    trimatrix T = new_trimatrix(N);
    Hessenberg(&A, &T);

    // Print the tridiagonal matrix
    printf("Tridiagonal Matrix (Phase 1 Result):\n");
    print_trimatrix(&T); 

    // Step 4: Apply QR Algorithm to get eigenvalues (Phase 2)
    QRA(&T);

    // Print the final eigenvalues
    printf("Eigenvalues (Phase 2 Result):\n");
    for (int i = 1; i <= N; i++) {
        printf("Eigenvalue %d: %.6f\n", i, tget(&T, i, i));
    }

    delete_matrix(&L);
    delete_matrix(&A);
    delete_trimatrix(&T);

    return 0;
}
