import matplotlib.pyplot as plt
import numpy as np

# Reading data from file
x_values, y_values = np.loadtxt("chebyshev_data.txt", unpack=True)

# Ploting result
plt.plot(x_values, y_values, label="pN(x) using Chebyshev Expansion", color='b')
plt.xlabel("x")
plt.ylabel("pN(x)")
plt.title("Chebyshev Polynomial Expansion")
plt.legend()
plt.grid()
plt.show()
