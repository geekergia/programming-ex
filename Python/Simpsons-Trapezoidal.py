import numpy as np

def trapezoidal(f, a, b, n):
    result = 0.5*f(a) + 0.5*f(b)
    step = (b-a)/n

    x = a
    for i in range(1, n):
        x += step
        value = f(x)
        result += value

    return result

def simpson(f, a, b, n):
    if n%2 is not 0:
        return None

    step = (b - a)/n
    first = f(a)
    last = f(b)

    x = a
    total = 0

    for i in range(0,n-1):
        x += step
        value = f(x)

        if i%2 == 0:
            total += 4 * value
        else:
            total += 2 * value
    
    result = (step/3)*(first+total+last)
    return result

def ratio_trap(error, h):
	return error/(h**2)

def ratio_simp(error, h):
	return error/(h**4)

def error(f,f2):
	exact = f(1.5) - f(1)
	error = exact - f2

	return error

def application():
    from math import exp
    v = lambda x: (x**2)*(np.log(x))
    h = input('h: ')
    n = (1.5-1)/float(h) 
    trap = trapezoidal(v, 1, 1.5, int(n))
    simp = simpson(v,  1, 1.5, int(n))
    print("Apply Composite Trapezoidal Rule: ", trap)
    print("Apply Composite Simpsons Rule: ", simp)

    error_trap = error(v, trap)
    error_simp = error(v, simp)
    print("Error after applying Composite Trapezoidal Rule: ", error_trap)
    print("Error after applying Composite Simpsons Rule: ",error_simp)

    ratio_1 = ratio_trap(error_trap, float(h))
    ratio_2 = ratio_simp(error_simp, float(h))
    print("Ratio of error/h^2: ", ratio_1)
    print("Ratio of error/h^4: ", ratio_2)

if __name__ == '__main__':
    application()