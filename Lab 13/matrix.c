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

// Print a matrix
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

// Add two matrices
matrix matrix_add(const matrix* A, const matrix* B) {
    assert(A->rows == B->rows && A->cols == B->cols);
    matrix C = new_matrix(A->rows, A->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(C, i, j) = mgetp(A, i, j) + mgetp(B, i, j);
    return C;
}

// Subtract two matrices
matrix matrix_sub(const matrix* A, const matrix* B) {
    assert(A->rows == B->rows && A->cols == B->cols);
    matrix C = new_matrix(A->rows, A->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(C, i, j) = mgetp(A, i, j) - mgetp(B, i, j);
    return C;
}

// Multiply two matrices
matrix matrix_mult(const matrix* A, const matrix* B) {
    assert(A->cols == B->rows);  
    matrix C = new_matrix(A->rows, B->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= B->cols; j++)
            for (int k = 1; k <= A->cols; k++)
                mget(C, i, j) += mgetp(A, i, k) * mgetp(B, k, j);
    return C;
}

// Element-wise multiplication of two matrices
matrix matrix_dot_mult(const matrix* A, const matrix* B) {
    assert(A->rows == B->rows && A->cols == B->cols);
    matrix C = new_matrix(A->rows, A->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(C, i, j) = mgetp(A, i, j) * mgetp(B, i, j);
    return C;
}

// Create a new vector
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

// printing a vector
void print_vector_full(const vector* vec, char* varname) {
    assert(vec->size > 0);
    printf("\n%s = | ", varname);
    for (int i = 1; i <= vec->size; i++) {
        printf("%10.3e ", vgetp(vec, i));
    }
    printf("|\n");
}

// Adding two vectors
vector vector_add(const vector* x, const vector* y) {
    assert(x->size == y->size);
    vector z = new_vector(x->size);
    for (int i = 1; i <= x->size; i++)
        vget(z, i) = vgetp(x, i) + vgetp(y, i);
    return z;
}

// Subtracting two vectors
vector vector_sub(const vector* x, const vector* y) {
    assert(x->size == y->size);
    vector z = new_vector(x->size);
    for (int i = 1; i <= x->size; i++)
        vget(z, i) = vgetp(x, i) - vgetp(y, i);
    return z;
}

// dot product of two vectors
double vector_dot_mult(const vector* x, const vector* y) {
    assert(x->size == y->size);
    double result = 0.0;
    for (int i = 1; i <= x->size; i++)
        result += vgetp(x, i) * vgetp(y, i);
    return result;
}

// Multiply matrix by vector
vector matrix_vector_mult(const matrix* A, const vector* x) {
    assert(A->cols == x->size);
    vector Ax = new_vector(A->rows);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            vget(Ax, i) += mgetp(A, i, j) * vgetp(x, j);
    return Ax;
}

// Transposing a matrix
matrix matrix_transpose(const matrix* A) {
    matrix At = new_matrix(A->cols, A->rows);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(At, j, i) = mgetp(A, i, j);
    return At;
}

// Solve Ax = b using Gaussian elimination
vector solve(const matrix* A, const vector* b) {
    int n = A->rows;
    matrix U = *A;
    vector y = *b;
    vector x = new_vector(n);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double factor = mgetp(A, j, i) / mgetp(A, i, i);
            for (int k = i; k <= n; k++) {
                mgetp(A, j, k) -= factor * mgetp(A, i, k);
            }
            vgetp(&y, j) -= factor * vgetp(&y, i);  
        }
    }

    for (int i = n; i >= 1; i--) {
        x.val[i - 1] = vgetp(&y, i);  
        for (int j = i + 1; j <= n; j++) {
            x.val[i - 1] -= mgetp(A, i, j) * x.val[j - 1];
        }
        x.val[i - 1] /= mgetp(A, i, i);
    }
    return x;
}