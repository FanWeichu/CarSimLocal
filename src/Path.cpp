//
// Created by 范惟楚 on 22.08.22.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "../include/Path.h"

Path::Path() {
  x_path_.clear();
  y_path_.clear();
}
Path::~Path() {
}

void Path::PathGen() {
  double straight_len_1 = 20.0;
  int point_per_meter = 5;
  double distance_between_points = 1.0 / 5;
  double temp_x = 0.;
  double temp_y = 0.;
  int sum_point_1 = static_cast<int>(straight_len_1 * point_per_meter);

  for (int i = 0; i < sum_point_1; ++i) {
    x_path_.push_back(temp_x);
    y_path_.push_back(temp_y);
    temp_x = temp_x + distance_between_points;
    temp_y = temp_y;
  }

  double circle_angle = 3.14 / 2;
  double start_angle = -3.14 / 2;
  double diff_between_points = 0.05;

}

void Path::LoadCsvPath() {
  std::vector<std::string> vec_info;
  std::vector<double> path_;
  std::ifstream data("../path.csv");
  if (data.is_open()) {
    std::string line;
    while (std::getline(data, line)) {
      std::istringstream sin(line);
//      std::cout<< line << std::endl;
      std::string info;
      while (std::getline(sin, info, ',')) {
        vec_info.push_back(info);
      }
    }
    for (int i = 0; i < vec_info.size() / 2; ++i) {
      x_path_.emplace_back(std::stold(vec_info[i * 2]));
      y_path_.emplace_back(std::stold(vec_info[i * 2 +1]));
    }
  }
  for (int i = 0; i < x_path_.size(); ++i) {
    if (i == 0) {
      double temp_dx = x_path_[1] - x_path_[0];
      double temp_dy = y_path_[1] - y_path_[0];
      double temp_theta = acos(temp_dx / (sqrt(pow(temp_dx, 2) + pow(temp_dy, 2))));
      theta_path_.emplace_back(temp_theta);
//      std::cout<<"i = "<<i<<", theta = "<<theta_path_[i]<<std::endl;
    } else {
      double temp_dx = x_path_[i] - x_path_[i - 1];
      double temp_dy = y_path_[i] - y_path_[i - 1];
      double temp_theta = acos(temp_dx / (sqrt(pow(temp_dx, 2) + pow(temp_dy, 2))));
      theta_path_.emplace_back(temp_theta);
//      std::cout<<"i = "<<i<<", theta = "<<theta_path_[i] * 57.3<<std::endl;
    }
  }
}

int Path::FindIdxNearstPoint(double x_car, double y_car) {
  int idx_min_d = 0;
  double dist_min = 99999;
  double dist_now = 0;
  for (int i = 0; i < x_path_.size(); ++i) {
    dist_now = pow((x_car - x_path_[i]), 2) + pow((y_car - y_path_[i]), 2);
    if (dist_now < dist_min) {
      dist_min = dist_now;
      idx_min_d = i;
    }
  }
  return idx_min_d;
}

double Path::GetLatErr(int idx_ref, double x_car, double y_car) {
  double ed = 0;
  double theta_ref = theta_path_[idx_ref];
  double x_ref = x_path_[idx_ref];
  double y_ref = y_path_[idx_ref];
  double vec_norm_x = -sin(theta_ref);
  double vec_norm_y = cos(theta_ref);
//  double vec_dx = x_car - x_ref;
//  double vec_dy = y_car - y_ref;
  double vec_dx = x_ref - x_car;
  double vec_dy = y_ref - y_car;
  ed = vec_norm_x * vec_dx + vec_norm_y * vec_dy;
  return ed;
}

double Path::GetPsiErr(int idx_ref, double psi_car) {
  double epsi = 0;
  epsi = theta_path_[idx_ref] - psi_car;
  return epsi;
}


