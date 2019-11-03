import numpy as np
import matplotlib.pyplot as plot

def fun(x):
    return (np.cos(3*x) / x) ** 2

X = np.linspace(0.3, np.pi, 500)
Y = [fun(x) for x in X]

plot.plot(X, Y)
plot.show()
