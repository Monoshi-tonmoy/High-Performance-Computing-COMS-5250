#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <assert.h>

typedef struct {
    int size;
    double* data;
} vector;

vector new_vector(int N) {
    vector v;
    v.size = N;
    v.data = (double*)malloc(N * sizeof(double));
    assert(v.data != NULL);
    return v;
}

void delete_vector(vector* v) {
    free(v->data);
    v->size = 0;
}

double vget(vector v, int i) {
    return v.data[i-1]; // 1-based indexing
}

void vset(vector v, int i, double val) {
    v.data[i-1] = val; // 1-based indexing
}

// Fine-grain 2-norm normalization
void normalize_fine_2norm(vector x, int thread_count) {
    double norm = 0.0;
    
    // Compute norm
    #pragma omp parallel for reduction(+:norm) num_threads(thread_count)
    for (int i = 1; i <= x.size; i++) {
        double val = vget(x, i);
        norm += val * val;
    }
    norm = sqrt(norm);
    
    // Normalize vector
    #pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= x.size; i++) {
        vset(x, i, vget(x, i) / norm);
    }
}

// Coarse-grain 2-norm normalization
void normalize_coarse_2norm(vector x, int thread_count) {
    double norm = 0.0;
    
    #pragma omp parallel num_threads(thread_count)
    {
        int my_rank = omp_get_thread_num();
        int N_per_thread = x.size / thread_count;
        int istart = my_rank * N_per_thread + 1;
        int iend = (my_rank + 1) * N_per_thread;
        
        // Handle case when size not divisible by thread_count
        if (my_rank == thread_count - 1) {
            iend = x.size;
        }
        
        double norm_thread = 0.0;
        for (int i = istart; i <= iend; i++) {
            double val = vget(x, i);
            norm_thread += val * val;
        }
        
        #pragma omp critical
        norm += norm_thread;
        
        #pragma omp barrier // Ensure all threads have contributed to norm
        
        for (int i = istart; i <= iend; i++) {
            vset(x, i, vget(x, i) / sqrt(norm));
        }
    }
}

// Fine-grain max-norm normalization
void normalize_fine_maxnorm(vector x, int thread_count) {
    double norm = 0.0;
    
    // Compute max norm
    #pragma omp parallel num_threads(thread_count)
    {
        double local_max = 0.0;
        #pragma omp for
        for (int i = 1; i <= x.size; i++) {
            double val = fabs(vget(x, i));
            if (val > local_max) local_max = val;
        }
        
        #pragma omp critical
        {
            if (local_max > norm) norm = local_max;
        }
    }
    
    // Normalize vector
    #pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= x.size; i++) {
        vset(x, i, vget(x, i) / norm);
    }
}

// Coarse-grain max-norm normalization
void normalize_coarse_maxnorm(vector x, int thread_count) {
    double norm = 0.0;
    
    #pragma omp parallel num_threads(thread_count)
    {
        int my_rank = omp_get_thread_num();
        int N_per_thread = x.size / thread_count;
        int istart = my_rank * N_per_thread + 1;
        int iend = (my_rank + 1) * N_per_thread;
        
        // Handle case when size not divisible by thread_count
        if (my_rank == thread_count - 1) {
            iend = x.size;
        }
        
        double norm_thread = 0.0;
        for (int i = istart; i <= iend; i++) {
            double val = fabs(vget(x, i));
            if (val > norm_thread) norm_thread = val;
        }
        
        #pragma omp critical
        {
            if (norm_thread > norm) norm = norm_thread;
        }
        
        #pragma omp barrier // Ensure all threads have contributed to norm
        
        for (int i = istart; i <= iend; i++) {
            vset(x, i, vget(x, i) / norm);
        }
    }
}

double verify_2norm(vector x) {
    double norm = 0.0;
    for (int i = 1; i <= x.size; i++) {
        double val = vget(x, i);
        norm += val * val;
    }
    return sqrt(norm);
}

double verify_maxnorm(vector x) {
    double norm = 0.0;
    for (int i = 1; i <= x.size; i++) {
        double val = fabs(vget(x, i));
        if (val > norm) norm = val;
    }
    return norm;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <thread_count> <vector_size>\n", argv[0]);
        return 1;
    }
    
    int thread_count = atoi(argv[1]);
    int N = atoi(argv[2]);
    
    if (thread_count < 1 || N < 1) {
        printf("Invalid arguments\n");
        return 1;
    }
    
    // Create vectors
    vector x1 = new_vector(N); // For 2-norm (all ones)
    vector x2 = new_vector(N); // For max-norm (1,2,...,N)
    
    // Initialize vectors
    #pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= N; i++) {
        vset(x1, i, 1.0);
        vset(x2, i, (double)i);
    }
    
    // Test 2-norm normalization
    printf("\n=== 2-NORM NORMALIZATION ===\n");
    
    // Fine-grain
    double start = omp_get_wtime();
    normalize_fine_2norm(x1, thread_count);
    double end = omp_get_wtime();
    printf("Fine-grain time: %.6f seconds\n", end - start);
    printf("Verified 2-norm after normalization: %.6f\n", verify_2norm(x1));
    
    // Reset vector
    #pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= N; i++) {
        vset(x1, i, 1.0);
    }
    
    // Coarse-grain
    start = omp_get_wtime();
    normalize_coarse_2norm(x1, thread_count);
    end = omp_get_wtime();
    printf("Coarse-grain time: %.6f seconds\n", end - start);
    printf("Verified 2-norm after normalization: %.6f\n", verify_2norm(x1));
    
    // Test max-norm normalization
    printf("\n=== MAX-NORM NORMALIZATION ===\n");
    
    // Fine-grain
    start = omp_get_wtime();
    normalize_fine_maxnorm(x2, thread_count);
    end = omp_get_wtime();
    printf("Fine-grain time: %.6f seconds\n", end - start);
    printf("Verified max-norm after normalization: %.6f\n", verify_maxnorm(x2));
    
    // Reset vector
    #pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= N; i++) {
        vset(x2, i, (double)i);
    }
    
    // Coarse-grain
    start = omp_get_wtime();
    normalize_coarse_maxnorm(x2, thread_count);
    end = omp_get_wtime();
    printf("Coarse-grain time: %.6f seconds\n", end - start);
    printf("Verified max-norm after normalization: %.6f\n", verify_maxnorm(x2));
    
    // Clean up
    delete_vector(&x1);
    delete_vector(&x2);
    
    return 0;
}