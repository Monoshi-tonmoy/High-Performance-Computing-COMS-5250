#include "matrix.h"

// dot product of two vectors
double vector_dot_mult(const vector* x, const vector* y) {
    assert(x->size == y->size);
    double result = 0.0;
    for (int i = 1; i <= x->size; i++)
        result += vgetp(x, i) * vgetp(y, i);
    return result;
}