#include "matrix.h"

matrix matrix_mult(const matrix* A, const matrix* B) {
    assert(A->cols == B->rows);  
    matrix C = new_matrix(A->rows, B->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= B->cols; j++)
            for (int k = 1; k <= A->cols; k++)
                mget(C, i, j) += mgetp(A, i, k) * mgetp(B, k, j);
    return C;
}