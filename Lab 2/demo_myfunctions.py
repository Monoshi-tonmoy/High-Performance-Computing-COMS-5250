import math

"""Square Root function using Newton's method"""
def sqrt(number, convergence_value=1e-6, max_iterations=100):
    if number == 0:
        return 0
    elif number < 0:
        print("Please enter a valid number for square root calculation")
        return

    s = number / 2

    for i in range(max_iterations):
        next_s = 0.5 * (s + number / s)
        
        if abs(next_s - s) < convergence_value:
            print(f"Converged after {i + 1} iterations.")
            return next_s
        
        s = next_s
        
        print(f"After {i + 1}th iteration the value is: {s}")

    return s

"""Factorial Function"""
def fact(number):

    if number == 1 or number == 0:
        return 1
    return number * fact(number-1)

"""Exponential function using Taylor series expansion"""
def exp(x, terms=18):
    x0 = int(round(x))
    
    e_x0 = math.exp(x0)
    
    z = x - x0
    
    result = e_x0

    term = 1 
    for n in range(1, terms + 1):
        term *= z / n
        result += term
    
    return result


"""Logarithm Calculation"""
def ln(x, convergence_value=1e-6, max_iterations=100):
    if x <= 0:
        print("Input must be a positive number.")
        return None
    
    s = x
    
    for i in range(max_iterations):
        exp_s = math.exp(s)
        
        next_s = s - (exp_s - x) / exp_s
        
        if abs(next_s - s) < convergence_value:
            print(f"Converged after {i + 1} iterations.")
            return next_s
        
        s = next_s
    
    print("Maximum iterations reached.")
    return s


def main():
    value = int(input("Enter a value to calculate square root, factorial, e^value and ln(value):"))
    print("\n................Here is the Results for Square Root function...............\n")
    square_root_value = sqrt(value)
    print(f"Final Square root value is {square_root_value}")
    print("\n\n")

    print("\n................Here is the Results for Factorial function...............\n")
    print(f"Final factorial value is {fact(value)}")
    print("\n\n")

    print("\n................Here are the Results for the Exponential function...............\n")
    exp_value = exp(value)
    print(f"Final value of e^{value} is {exp_value}")
    print("\n\n")

    print("\n................Here are the Results for the Logarithmic function...............\n")
    ln_value = ln(value)
    print(f"Final value of ln({value}) is {ln_value}")
    print("\n\n")



if __name__ == "__main__":
    main()
