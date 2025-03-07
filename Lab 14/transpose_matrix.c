#include "matrix.h"

// Transposing a matrix
matrix matrix_transpose(const matrix* A) {
    matrix At = new_matrix(A->cols, A->rows);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(At, j, i) = mgetp(A, i, j);
    return At;
}