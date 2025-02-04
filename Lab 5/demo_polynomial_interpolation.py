import numpy as np
from gaussian_elimination import GaussElimination  # User-defined module
import matplotlib.pyplot as plt

# Getting points from given problem
points = np.array([-0.1, -0.02, 0.02, 0.1])
values = np.cos(points)

# Constructing Vandermonde matrix
A = np.vander(points, 4)

# Using our user defined module function to get the coefficients
coefficients = GaussElimination(A, values)
a, b, c, d = coefficients

# errorrs computing
p_values = np.polyval(coefficients, points)
errors = np.abs(values - p_values)
max_error = np.max(errors)

# Priting the results
print("Polynomial coefficients:", coefficients)
print("Maximum error:", max_error)

# Generate points for plotting
x_plot = np.linspace(-0.15, 0.15, 100)
f_values = np.cos(x_plot)
p_values_plot = np.polyval(coefficients, x_plot) 

print(f_values)
print(p_values)

# Plotting the cosine function graph and polynomial graph to see how they overlap
plt.figure(figsize=(10, 4))
plt.subplot(1, 2, 1)
plt.plot(x_plot, f_values, label="cos(x)", linestyle="dashed", color="blue", linewidth=2)
plt.plot(x_plot, p_values_plot, label="Interpolating Polynomial", linestyle="solid", color="red", linewidth=1)
plt.scatter(points, values, color="black", label="Interpolation Points")
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.title("Polynomial Interpolation of cos(x)")


plt.tight_layout()
plt.show()
