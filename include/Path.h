//
// Created by 范惟楚 on 22.08.22.
//

#ifndef CARSIMLOCAL_SRC_PATH_H_
#define CARSIMLOCAL_SRC_PATH_H_

#include <vector>
#include <cmath>

class Path {
 public:
  Path();
  ~Path();
  void PathGen();
  void LoadCsvPath();
  int FindIdxNearstPoint(double x_car, double y_car);
  double GetLatErr(int idx_ref, double x_car, double y_car);
  double GetPsiErr(int idx_ref, double psi_car);


  std::vector<double>(x_path_); std::vector<double>(y_path_); std::vector<double>(theta_path_);
  int idx_min_d_ = 0;

 private:

};

#endif //CARSIMLOCAL_SRC_PATH_H_
