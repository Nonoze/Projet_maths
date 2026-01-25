import numpy as np
from io import StringIO


with open("data.csv", "r") as f:
	csv_text = f.read()

arr = np.genfromtxt(StringIO(csv_text), delimiter=",", skip_header=1, dtype=int)

length = arr[:, 0]
segment = arr[:, 1] + 1

print(segment[:]) 
import matplotlib.pyplot as plt

valid = length > 0
x = length[valid]
y = segment[valid] / np.sqrt(x)

plt.plot(x, y, linewidth=1.5, label=r'$\frac{m(\ell)}{\sqrt{\ell}}$')
plt.axhline(1.8, linestyle=":", color="tab:red", linewidth=1.0, label="bornes")
plt.axhline(1.7, linestyle=":", color="tab:red", linewidth=1.0)
plt.xlabel(r'$\ell$')
plt.ylabel(r'$\frac{m(\ell)}{\sqrt{\ell}}$')
plt.title(r'Rapport $\frac{m(\ell)}{\sqrt{\ell}}$ en fonction de la longueur $\ell$')
plt.legend()
plt.tight_layout()
plt.savefig("graph_segment_over_sqrt_length.png")
# plt.show()

plt.figure()
fx = segment[valid]

plt.plot(x, fx, label=r'$m(\ell)$', linewidth=1.5)
plt.xlabel(r'$\ell$')
plt.ylabel(r'$m(\ell)$')
plt.title(r'Nombre de graduations $m(\ell)$ en fonction de la longueur $\ell$')
plt.legend()
plt.tight_layout()
plt.savefig("graph_f.png")
# plt.show()
plt.figure()
plt.plot(x, fx, label=r'$m(\ell)$', linewidth=1.5)

# Calcul des fonctions h1..h6
mask_50 = x > 50
mask_51 = x > 51

sx = np.sqrt(x)
sx_50 = np.sqrt(x[mask_50] - 50)
sx_51 = np.sqrt(x[mask_51] - 51)

h1 = (1.697 + 1 / sx_50) * np.sqrt(x[mask_50])
h2 = (1.697 - 1 / sx_50) * np.sqrt(x[mask_50])
h3 = (1.82 + 1 / sx_51) * np.sqrt(x[mask_51])
h4 = (1.82 - 1 / sx_51) * np.sqrt(x[mask_51])
h5 = 1.4 * sx
h6 = 2 * sx

# plt.plot(x[mask_50], h1, linestyle=":", color="tab:orange", label="h1(x)")
# plt.plot(x[mask_50], h2, linestyle=":", color="tab:orange", label="h2(x)")
# plt.plot(x[mask_51], h3, linestyle=":", color="tab:green", label="h3(x)")
# plt.plot(x[mask_51], h4, linestyle=":", color="tab:green", label="h4(x)")
# plt.plot(x, h5, linestyle="-.", color="tab:red", label="h5(x)")
# plt.plot(x, h6, linestyle="-.", color="tab:red", label="h6(x)")
plt.plot(x, h5, linestyle="--", color="tab:red", label="bornes")
plt.plot(x, h6, linestyle="--", color="tab:red")

plt.xlabel(r'$\ell$')
plt.ylabel(r'$m(\ell)$')
# plt.title("f(x) et fonctions h1..h6")
plt.title(r'Nombre de graduations $m(\ell)$ en fonction de la longueur $\ell$ avec bornes')
plt.legend()
plt.tight_layout()
plt.savefig("graph_f_bornes.png")
# plt.show()