#include "matrix.h"

/*Using Functions from our lecture slides*/


// Create a new matrix
matrix new_matrix(const int rows, const int cols) {
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    assert(rows > 0);
    assert(cols > 0);
    mat.val = (double*)malloc(sizeof(double) * rows * cols);
    for (int i = 0; i < rows * cols; i++) {
        mat.val[i] = 0.0;
    }
    return mat;
}