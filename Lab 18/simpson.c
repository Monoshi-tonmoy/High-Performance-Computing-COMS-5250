#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
# include <omp.h>
#endif

//Same function as lecture for trapezoidal
double func(const double x) {
    return (1.0 + exp(x)); 
}

double SerialSimpson(const double a, const double b, const int N) {
    double h = (b-a)/N;
    double sum = func(a) + func(b);
    
    for (int i = 1; i < N; i++) {
        double x = a + i*h;
        sum += (i % 2 == 1) ? 4.0 * func(x) : 2.0 * func(x);
    }
    
    return (h/3.0) * sum;
}

double ParallelSimpsonCritical(const double a, const double b, const int N, const int thread_count) {
    double h = (b-a)/N;
    double global_sum = func(a) + func(b);
    
    #pragma omp parallel num_threads(thread_count)
    {
        double local_sum = 0.0;
        #ifdef _OPENMP
        int my_rank = omp_get_thread_num();
        int threads = omp_get_num_threads();
        #else
        int my_rank = 0;
        int threads = 1;
        #endif
        int chunk_size = N/threads;
        int start = my_rank * chunk_size;
        int end = (my_rank == threads-1) ? N-1 : (my_rank+1)*chunk_size;
        
        for (int i = start+1; i < end; i++) {
            double x = a + i*h;
            local_sum += (i % 2 == 1) ? 4.0 * func(x) : 2.0 * func(x);
        }
        
        #pragma omp critical
        global_sum += local_sum;
    }
    
    return (h/3.0) * global_sum;
}

double ParallelSimpsonReduction(const double a, const double b, const int N, const int thread_count) {
    double h = (b-a)/N;
    double sum = func(a) + func(b);
    
    #pragma omp parallel for num_threads(thread_count) reduction(+:sum)
    for (int i = 1; i < N; i++) {
        double x = a + i*h;
        sum += (i % 2 == 1) ? 4.0 * func(x) : 2.0 * func(x);
    }
    
    return (h/3.0) * sum;
}

int main(int argc, char* argv[]) {
    void usage(const char* prog_name);
    
    if (argc != 3) { usage(argv[0]); }
    const int thread_count = strtol(argv[1], NULL, 10);
    const int N = strtol(argv[2], NULL, 10);
    
    // Ensure N is divisible by thread_count and even
    if (thread_count < 1 || N < 2 || N % thread_count != 0 || N % 2 != 0) { 
        usage(argv[0]); 
    }
    
    const double a = 0.0; const double b = 1.0;
    double Iex = exp(1.0);
    
    // Serial version
    double time1 = omp_get_wtime();
    double T_serial = SerialSimpson(a, b, N);
    double time2 = omp_get_wtime();
    double err_serial = fabs(T_serial - Iex);
    
    // Critical version
    time1 = omp_get_wtime();
    double T_critical = ParallelSimpsonCritical(a, b, N, thread_count);
    time2 = omp_get_wtime();
    double err_critical = fabs(T_critical - Iex);
    double time_critical = time2 - time1;
    
    // Reduction version
    time1 = omp_get_wtime();
    double T_reduction = ParallelSimpsonReduction(a, b, N, thread_count);
    time2 = omp_get_wtime();
    double err_reduction = fabs(T_reduction - Iex);
    double time_reduction = time2 - time1;
    
    printf("\nN = %d, Threads = %d\n", N, thread_count);
    printf("Serial:     T = %23.15e, err = %12.5e\n", T_serial, err_serial);
    printf("Critical:   T = %23.15e, err = %12.5e, time = %12.5e\n", 
           T_critical, err_critical, time_critical);
    printf("Reduction:  T = %23.15e, err = %12.5e, time = %12.5e\n\n", 
           T_reduction, err_reduction, time_reduction);
    
    return 0;
}

void usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s <num_threads> <num_intervals>\n", prog_name);
    fprintf(stderr, "  num_threads should be positive (1, 2, 4, 8, 16)\n");
    fprintf(stderr, "  num_intervals should be even and divisible by num_threads\n");
    fprintf(stderr, "  Suggested N: 16777216 (divisible by 1,2,4,8,16)\n");
    exit(1);
}