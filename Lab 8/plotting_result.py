import matplotlib.pyplot as plt
import numpy as np

# Load data from the file
data = np.loadtxt("exp_data.txt", delimiter=",", skiprows=1)
x_values, y_values = data[:, 0], data[:, 1]

# Plotting the exp() with values from defined function
plt.figure(figsize=(8, 5))
plt.plot(x_values, y_values, marker='o', linestyle='-', color='b', label='exp(x) - Taylor series')

# Curve using numpy
x_ref = np.linspace(0, 1, 100)
y_ref = np.exp(x_ref)
plt.plot(x_ref, y_ref, linestyle='dashed', color='r', label='exp(x) - Numpy')

plt.xlabel("x")
plt.ylabel("exp(x)")
plt.title("Approximation of exp(x) using Taylor Series")
plt.legend()
plt.grid(True)
plt.show()
