#include "matrix.h"

matrix matrix_add(const matrix* A, const matrix* B) {
    assert(A->rows == B->rows && A->cols == B->cols);
    matrix C = new_matrix(A->rows, A->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(C, i, j) = mgetp(A, i, j) + mgetp(B, i, j);
    return C;
}