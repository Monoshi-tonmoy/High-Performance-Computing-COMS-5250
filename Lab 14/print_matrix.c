#include "matrix.h"

void print_matrix_full(const matrix* mat, char* varname) {
    assert(mat->rows > 0 && mat->cols > 0);
    printf("\n%s =\n", varname);
    for (int i = 1; i <= mat->rows; i++) {
        printf("| ");
        for (int j = 1; j <= mat->cols; j++) {
            printf("%10.3e ", mgetp(mat, i, j));
        }
        printf("|\n");
    }
}
