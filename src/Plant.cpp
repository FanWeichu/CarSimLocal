//
// Created by 范惟楚 on 22.08.22.
//

#include "../include/Plant.h"
Plant::Plant() {
  x_ = 0.;
  y_ = 0.;
  psi_ = 0.;
  v_ = 0.;
  delta_ = 0.;
  t_global_ = 0.;
}
Plant::~Plant() {
}

void Plant::Sim(double vel, double delta, double T) {
  x_dot = vel * cos(psi_);
  y_dot = vel * sin(psi_);
  psi_dot = (vel * tan(delta)) / wheel_base;
  x_ = x_ + x_dot * T;
  y_ = y_ + y_dot * T;
  psi_ = psi_ + psi_dot * T;
  t_global_ = t_global_ + T;
}

