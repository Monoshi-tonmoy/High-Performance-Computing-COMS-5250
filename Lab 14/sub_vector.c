#include "matrix.h"

// Subtracting two vectors
vector vector_sub(const vector* x, const vector* y) {
    assert(x->size == y->size);
    vector z = new_vector(x->size);
    for (int i = 1; i <= x->size; i++)
        vget(z, i) = vgetp(x, i) - vgetp(y, i);
    return z;
}