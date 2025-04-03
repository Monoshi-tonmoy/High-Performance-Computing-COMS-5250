#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Function prototypes
double AdaptiveInt(const double a, const double b, const double TOL, 
                  const int num_threads);
double AdaptiveIntSerial(const double a, const double b, const double TOL);
double Q(const double a, const double b);
double f(const double x);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_threads> <TOL>\n", argv[0]);
        fprintf(stderr, "  num_threads should be positive\n");
        fprintf(stderr, "  TOL should be positive\n");
        return 1;
    }

    const int thread_count = atoi(argv[1]);
    const double TOL = atof(argv[2]);

    if (thread_count < 1 || TOL < 5.0e-16) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    const double a = -2.0;
    const double b = 4.0;
    const double exact = 0.4147421694070212;

    // Enable nested parallelism
    omp_set_nested(1);
    omp_set_dynamic(0);

    double I;
    if (thread_count == 1) {
        I = AdaptiveIntSerial(a, b, TOL);
    } else {
        I = AdaptiveInt(a, b, TOL, thread_count);
    }

    printf("\n thread_count = %i\n", thread_count);
    printf(" TOL = %24.15e\n", TOL);
    printf(" I = %24.15e\n", I);
    printf(" err = %24.15e\n\n", fabs(I - exact));

    return 0;
}

double AdaptiveInt(const double a, const double b, const double TOL, 
                 const int num_threads) {
    double Qab = Q(a, b);
    const double c = 0.5 * (a + b);
    double Qac = Q(a, c);
    double Qcb = Q(c, b);

    const double one_over_15 = 6.666666666666667e-02;
    const double error_est = one_over_15 * fabs(Qac + Qcb - Qab);

    if (error_est < TOL) {
        return Qac + Qcb;
    } else {
        double result = 0.0;
        #pragma omp parallel num_threads(num_threads) reduction(+:result)
        {
            const int my_rank = omp_get_thread_num();
            const double width = (b - a) / num_threads;
            const double a_local = a + my_rank * width;
            const double b_local = a_local + width;
            const double TOL_local = TOL / num_threads;

            result += AdaptiveInt(a_local, b_local, TOL_local, num_threads);
        }
        return result;
    }
}

double AdaptiveIntSerial(const double a, const double b, const double TOL) {
    double Qab = Q(a, b);
    const double c = 0.5 * (a + b);
    double Qac = Q(a, c);
    double Qcb = Q(c, b);

    const double one_over_15 = 6.666666666666667e-02;
    const double error_est = one_over_15 * fabs(Qac + Qcb - Qab);

    if (error_est < TOL) {
        return Qac + Qcb;
    } else {
        double result = AdaptiveIntSerial(a, c, 0.5 * TOL);
        result += AdaptiveIntSerial(c, b, 0.5 * TOL);
        return result;
    }
}

double Q(const double a, const double b) {
    const double one_sixth = 1.666666666666667e-01;
    const double c = 0.5 * (a + b);
    return one_sixth * (b - a) * (f(a) + 4.0 * f(c) + f(b));
}

double f(const double x) {
    const double beta = 10.0;
    return exp(-pow(beta * x, 2)) + sin(x);
}