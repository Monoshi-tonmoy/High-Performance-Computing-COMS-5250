#include "matrix.h"

vector new_vector(const int size) {
    vector vec;
    vec.size = size;
    assert(size > 0);
    vec.val = (double*)malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        vec.val[i] = 0.0;
    }
    return vec;
}
