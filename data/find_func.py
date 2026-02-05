import numpy as np
from io import StringIO
from scipy.optimize import curve_fit
from math import floor

with open("data.csv", "r") as f:
	csv_text = f.read()

arr = np.genfromtxt(StringIO(csv_text), delimiter=",", skip_header=1, dtype=int)

length = arr[:, 0]
segment = arr[:, 1] + 1

# objective: find a function f(x)=sqrt(mx+p) that fits the data (x, segment)
# we can take the square of both sides: f(x)^2 = mx + p
valid = length > 0
x = length[valid]
y = segment[valid]
def model_func(x, p):
	return np.sqrt(3.0 * x + p)


params, covariance = curve_fit(model_func, x, y, p0=[2.0])

m_fit, p_fit = 3.0, params[0]
print(f"Fitted parameters: m = {m_fit}, p = {p_fit}")

p_fit=2.25
m_fit=3.00

cntwrong=0
for i in range(len(x)):
	fitted_value = round(model_func(x[i], p_fit))
	if fitted_value != y[i]:
		cntwrong += 1
		print(f"At x={x[i]}, actual={y[i]}, fitted={fitted_value}")

print(f"Number of mismatches: {cntwrong} out of {len(x)}")