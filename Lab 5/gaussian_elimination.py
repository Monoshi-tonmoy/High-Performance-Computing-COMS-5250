import numpy as np

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
