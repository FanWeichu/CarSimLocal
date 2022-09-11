import re
import numpy as np
import matplotlib.pyplot as plt
import csv
import os

current_path = os.getcwd()
# data_path = current_path + '/data_analyse'
csv_file = open('data_analyse/ControlResult.csv', 'r')
dict_file = csv.DictReader(csv_file)
csv.field_size_limit(100000000)
var_list = [var for var in dict_file.fieldnames if var != '']

x_path = []
y_path = []
with open('path.csv', 'r') as path_csv:
    path_reader = csv.reader(path_csv)
    for line in path_reader:
        x_path.append(line[0])
        y_path.append(line[1])

x_path = np.array(x_path).reshape(-1, 1).astype(float)
y_path = np.array(y_path).reshape(-1, 1).astype(float)

np_path = np.hstack((x_path, y_path))

for var in var_list:
    globals()['li_' + var] = []

for row in dict_file:
    for var in var_list:
        temp_value = float(row[var])
        eval('li_' + var + '.append(temp_value)')

for var in var_list:
    globals()['np_' + var] = np.array(eval('li_' + var)).reshape(-1, 1)




plt.figure()
plt.plot(np_x_car, np_y_car, 'r', label='car_path')
plt.plot(np_path[:,0], np_path[:, 1], 'b', label='path')
# plt.plot(np_target_x, np_target_y, 'b', label='ref_path')
plt.title('Traj car')
plt.axis('equal')
plt.legend()

plt.figure()
plt.plot(np_t, np_delta, label='delta')
plt.title('delta')
plt.legend

# plt.figure()
# plt.plot(np_t, np_e_dist, label='e_dist')
# plt.title('e_dist')
# plt.legend

# plt.figure()
# plt.plot(np_t, np_e_psi, label='e_psi')
# plt.title('e_psi')
# plt.legend

# plt.figure()
# plt.plot(np_t, np_psi, 'r', label='psi')
# plt.plot(np_t, np_d_psi, 'b', label='d_psi')
# plt.plot(np_t, np_ref_psi, 'c', label='ref_psi')
# plt.title('psi')
# plt.legend()
#
# plt.figure()
# plt.plot(np_t, np_d_x, 'r', label='d_x')
# plt.plot(np_t, np_d_y, 'b', label='d_y')
# plt.title('dist_x_y')
# plt.legend()
#
# plt.figure()
# plt.plot(np_t, np_steering_angle, 'r', label='steering_angle')
# plt.title('steering_angle')
# plt.legend()
# # plt.figure()
# # plt.plot(np_t, np_psi)

plt.show()