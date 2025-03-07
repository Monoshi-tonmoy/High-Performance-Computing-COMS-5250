#include "matrix.h"

vector matrix_vector_mult(const matrix* A, const vector* x) {
    assert(A->cols == x->size);
    vector Ax = new_vector(A->rows);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            vget(Ax, i) += mgetp(A, i, j) * vgetp(x, j);
    return Ax;
}
