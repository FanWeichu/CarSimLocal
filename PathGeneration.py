import numpy as np
import matplotlib.pyplot as plt
import csv
import os

pi = np.pi
p_init = np.array([0, 0])

d_interp = 0.2
l_1_length = 20
l_1_size = int(l_1_length / d_interp) + 1
l_1 = np.zeros([l_1_size, 2])

l_1[:, 1] = 0.0
for i in range(l_1_size):
    l_1[i, 0] = d_interp * i + p_init[0]

c_1_radius = 15
d_c_1_interp = d_interp / c_1_radius
c_1_angle = pi
c_1_size = int(c_1_angle / d_c_1_interp) + 1
c_1 = np.zeros([c_1_size, 2])

for i in range(c_1_size):
    c_1[i, 0] = l_1[-1, 0] + np.cos((i + 1) * d_c_1_interp - 0.5 * pi) * c_1_radius
    c_1[i, 1] = l_1[-1, 1] + c_1_radius + np.sin((i + 1) * d_c_1_interp - 0.5 * pi) * c_1_radius

# c_2_radius = 5
c_2_radius = 10
d_c_2_interp = d_interp / c_2_radius
c_2_angle = pi
c_2_size = int(c_2_angle / d_c_2_interp) + 1
c_2 = np.zeros([c_2_size, 2])

for i in range(c_2_size):
    c_2[i, 0] = c_1[-1, 0] + np.cos((3 / 2) * pi - (i + 1) * d_c_2_interp) * c_2_radius
    c_2[i, 1] = c_1[-1, 1] + c_2_radius + np.sin((3 / 2) * pi - (i + 1) * d_c_2_interp) * c_2_radius

l_2_length = 15
l_2_size = int(l_2_length / d_interp) + 1
l_2 = np.zeros([l_2_size, 2])

for i in range(l_2_size):
    l_2[i, 0] = c_2[-1, 0] + d_interp * (i + 1)
    l_2[:, 1] = c_2[-1, 1]

path = np.vstack((l_1, c_1, c_2, l_2))

csv_header = ['path_x', 'path_y']
with open('path.csv', 'w') as f:
    writer = csv.writer(f)
    # writer.writerow(csv_header)
    writer.writerows(path)

plt.figure()
plt.plot(path[:, 0], path[:, 1], '.')
plt.axis('equal')
plt.show()
print('finished')
