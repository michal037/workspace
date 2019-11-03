import numpy as np
from scipy.interpolate import interp1d
import matplotlib.pyplot as plot

x = [-1.0, -0.5,  0.24, 0.76, 1.0]
y = [0.0,  -0.6, -0.95, -0.21, 0.0]

xkw = np.linspace(-1, 1, 50, True)
fcubic = interp1d(x, y, 'cubic')

plot.plot(x, y, 'o', x, y, '--', xkw, fcubic(xkw), '-')
plot.legend(["Węzły", "Interpolacja liniowa", "Interpolacja kwadratowa"])
plot.show()
