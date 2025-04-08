#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>

double func(double x) {
    return exp(x);  // Function to integrate: e^x
}

double CompTrap(double a, double b, int N, double h) {
    double T = 0.5*(func(a) + func(b));
    for (int i = 1; i < N; i++) {
        T += func(a + i*h);
    }
    return h*T;
}

void get_input(int my_rank, int comm_sz, double* a, double* b, int* N) {
    if (my_rank == 0) {
        printf("Enter a, b, and N (N must be divisible by %d): ", comm_sz);
        scanf("%lf %lf %d", a, b, N);
        
        // Validate input
        if (*N <= 0 || *N % comm_sz != 0) {
            fprintf(stderr, "N must be positive and divisible by number of processors\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        
        // Broadcast input to other processes
        for (int i = 1; i < comm_sz; i++) {
            MPI_Send(a, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(b, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(a, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int comm_sz, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    double a, b, local_T, global_T;
    int N;
    
    // Get input (process 0 reads, others receive)
    get_input(my_rank, comm_sz, &a, &b, &N);
    
    // Start timer
    double start_time = MPI_Wtime();
    
    // Calculate local trapezoidal rule
    double h = (b - a)/N;
    int local_N = N/comm_sz;
    double local_a = a + my_rank*local_N*h;
    double local_b = local_a + local_N*h;
    local_T = CompTrap(local_a, local_b, local_N, h);
    
    // Reduce results to process 0
    MPI_Reduce(&local_T, &global_T, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Output results
    if (my_rank == 0) {
        double exact = exp(b) - exp(a);
        double error = fabs(global_T - exact)/fabs(exact);
        double elapsed = MPI_Wtime() - start_time;
        
        printf("NP = %2d, N = %d, T = %20.13e\n", comm_sz, N, global_T);
        printf("Exact = %20.13e, Relative Error = %20.13e\n", exact, error);
        printf("Elapsed time = %20.13e seconds\n", elapsed);
    }
    
    MPI_Finalize();
    return 0;
}