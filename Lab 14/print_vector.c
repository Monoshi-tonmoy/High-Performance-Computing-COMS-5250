#include "matrix.h"

// printing a vector
void print_vector_full(const vector* vec, char* varname) {
    assert(vec->size > 0);
    printf("\n%s = | ", varname);
    for (int i = 1; i <= vec->size; i++) {
        printf("%10.3e ", vgetp(vec, i));
    }
    printf("|\n");
}