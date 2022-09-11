//
// Created by 范惟楚 on 22.08.22.
//

#ifndef CARSIMLOCAL__PLANT_H_
#define CARSIMLOCAL__PLANT_H_
#include <cmath>

class Plant {
 public:
  Plant();
  ~Plant();

  void Sim(double vel, double delta, double T);

  double x_, y_, psi_, v_, delta_, t_global_;

 private:
  double x_dot, y_dot, psi_dot;
  double wheel_base = 4.0;
};

#endif //CARSIMLOCAL__PLANT_H_
