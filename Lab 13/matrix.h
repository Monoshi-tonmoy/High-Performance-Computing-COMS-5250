#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*
This header is given in our lecture slides
*/

// Matrix and vector structures
typedef struct matrix matrix;
typedef struct vector vector;

struct matrix {
    int rows, cols;
    double* val;
};

struct vector {
    int size;
    double* val;
};

// Macros 
#define mget(mat, i, j) mat.val[(i - 1) * mat.cols + (j - 1)]
#define mgetp(mat, i, j) mat->val[(i - 1) * mat->cols + (j - 1)]
#define vget(vec, i) (vec.val[(i - 1)])
#define vgetp(vec, i) ((vec)->val[(i - 1)])

// Function declarations
matrix new_matrix(const int rows, const int cols);
void print_matrix_full(const matrix* mat, char* varname);
matrix matrix_add(const matrix* A, const matrix* B);
matrix matrix_sub(const matrix* A, const matrix* B);
matrix matrix_mult(const matrix* A, const matrix* B);
matrix matrix_dot_mult(const matrix* A, const matrix* B);
matrix matrix_transpose(const matrix* A);  // Added transpose function

vector new_vector(const int size);
void print_vector_full(const vector* vec, char* varname);
vector vector_add(const vector* x, const vector* y);
vector vector_sub(const vector* x, const vector* y);
double vector_dot_mult(const vector* x, const vector* y);

void print_scalar_full(const double* z, char* varname);
vector matrix_vector_mult(const matrix* A, const vector* x);
vector solve(const matrix* A, const vector* b);

#endif