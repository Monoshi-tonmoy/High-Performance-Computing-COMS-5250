#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifdef _OPENMP
# include <omp.h>
#endif

int main(int argc, char* argv[])
{
    void usage(const char* prog_name);
    
    // Default values if not provided
    int N = 500;
    int K = 50;
    int thread_count = 1;
    
    // Parse command line arguments
    if (argc >= 2) thread_count = strtol(argv[1], NULL, 10);
    if (argc >= 3) N = strtol(argv[2], NULL, 10);
    if (argc >= 4) K = strtol(argv[3], NULL, 10);
    
    if (thread_count <= 0 || N <= 0 || K <= 0) {
        usage(argv[0]);
        return 1;
    }
    
    // Allocate memory for vectors
    double* x = (double*)malloc(N * sizeof(double));
    double* u = (double*)malloc(N * sizeof(double));
    
    // Initialize random vector x
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        x[i] = (double)rand() / RAND_MAX; // Random value between 0 and 1
    }
    
    // Start timer
    double start_time = omp_get_wtime();
    
    // Parallel computation of polynomial series
    #pragma omp parallel for num_threads(thread_count)
    for (int i = 0; i < N; i++) {
        u[i] = 1.0; // First term in the series
        
        double x_power = x[i]; // Will store x_i^k
        for (int j = 1; j <= K; j++) {
            u[i] += x_power;
            x_power *= x[i]; // Efficiently compute x_i^(j+1)
        }
    }
    
    // End timer
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    
    // Print results (first 5 elements for verification)
    printf("First 5 elements of u:\n");
    for (int i = 0; i < 5 && i < N; i++) {
        printf("u[%d] = %f\n", i, u[i]);
    }
    
    printf("\nComputation with %d threads for N=%d, K=%d took %.6f seconds\n", 
           thread_count, N, K, elapsed_time);
    
    // Free memory
    free(x);
    free(u);
    
    return 0;
}

void usage(const char *prog_name)
{
    fprintf(stderr, "Usage: %s [thread_count] [N] [K]\n", prog_name);
    fprintf(stderr, "  thread_count: number of threads (default: 1)\n");
    fprintf(stderr, "  N: vector length (default: 500)\n");
    fprintf(stderr, "  K:(default: 50)\n");
    fprintf(stderr, "All values must be positive integers\n");
}