import numpy as np
import matplotlib.pyplot as plt

def GaussElimination(A, b):
    """ Solves Ax = b using Gaussian Elimination """
    n = len(b)
    A = A.astype(float)  # Ensure floating point division
    b = b.astype(float)

    # Forward elimination
    for i in range(n):
        max_row = np.argmax(abs(A[i:, i])) + i
        if i != max_row:
            A[[i, max_row]] = A[[max_row, i]]
            b[[i, max_row]] = b[[max_row, i]]

        # Make diagonal elements 1 and eliminate below
        for j in range(i+1, n):
            factor = A[j, i] / A[i, i]
            A[j, i:] -= factor * A[i, i:]
            b[j] -= factor * b[i]

    # Back substitution
    x = np.zeros(n)
    for i in range(n-1, -1, -1):
        x[i] = (b[i] - np.dot(A[i, i+1:], x[i+1:])) / A[i, i]

    return x


def LeastSquareApprox(x, f, n):
    """ Finds the least square approximation of data {x, f} by a polynomial of degree ≤ n """
    A = np.vander(x, n+1)  
    ATA = A.T @ A  # Normal equations coefficient matrix
    ATb = A.T @ f  # Normal equations right-hand side
    coefficients = GaussElimination(ATA, ATb)
    return coefficients

def main():
    # Given interpolation points
    x = np.linspace(-np.pi, np.pi, 51)
    f = np.cos(x)
    
    # approximinaiton of degree 5
    n = 5
    coefficients = LeastSquareApprox(x, f, n)
    
    # Generate points for plotting
    x_plot = np.linspace(-np.pi, np.pi, 200)
    f_values = np.cos(x_plot)
    p_values_plot = np.polyval(coefficients, x_plot)
    
    # Computing errors
    errors = np.abs(f - np.polyval(coefficients, x))
    max_error = np.max(errors)
    
    # Print quantitative results
    print("Polynomial coefficients:", coefficients)
    print("Maximum error:", max_error)
    
    # Function vs least square approximation using matplotlib
    plt.figure(figsize=(10, 5))
    plt.plot(x_plot, f_values, label="cos(x)", linestyle="dotted", color="blue", linewidth=2)
    plt.plot(x_plot, p_values_plot, label="Least Squares Approximation", linestyle="solid", color="red", linewidth=1)
    plt.scatter(x, f, color="black", label="Sample Points", s=10)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.title("Least Squares Polynomial Approximation of cos(x)")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
