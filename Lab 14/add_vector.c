#include "matrix.h"

// Adding two vectors
vector vector_add(const vector* x, const vector* y) {
    assert(x->size == y->size);
    vector z = new_vector(x->size);
    for (int i = 1; i <= x->size; i++)
        vget(z, i) = vgetp(x, i) + vgetp(y, i);
    return z;
}