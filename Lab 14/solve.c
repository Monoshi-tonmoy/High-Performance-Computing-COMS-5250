#include "matrix.h"

// Solve Ax = b using Gaussian elimination
vector solve(const matrix* A, const vector* b) {
    int n = A->rows;
    matrix U = *A;
    vector y = *b;
    vector x = new_vector(n);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double factor = mgetp(A, j, i) / mgetp(A, i, i);
            for (int k = i; k <= n; k++) {
                mgetp(A, j, k) -= factor * mgetp(A, i, k);
            }
            vgetp(&y, j) -= factor * vgetp(&y, i);  
        }
    }

    for (int i = n; i >= 1; i--) {
        x.val[i - 1] = vgetp(&y, i);  
        for (int j = i + 1; j <= n; j++) {
            x.val[i - 1] -= mgetp(A, i, j) * x.val[j - 1];
        }
        x.val[i - 1] /= mgetp(A, i, i);
    }
    return x;
}