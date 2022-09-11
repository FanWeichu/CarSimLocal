#include <iostream>
#include "include/Plant.h"
#include "include/Path.h"
#include "filesystem"
#include "fstream"

int main() {
//  double value[] = {1, 2, 3};
//  double *x;
//  x = value;
//  std::cout << *x + 1 << std::endl;

  std::string data_analyse_folder = "../data_analyse";
  double vel = 1.0;
  double delta = 0.0;
  double T = 1.0 / 20.0;
  double sim_time = 80.;
  int N_sim = sim_time / T;
  int csv_title = 0;

  Path path;
  Plant plant;

  path.LoadCsvPath();

  if (path.x_path_.size() != path.y_path_.size()) {
    std::cout << "path size error!" << std::endl;
  } else {
    std::cout<< "path size check successful!" << std::endl;
  }

  std::ofstream OutFile;
  if (std::filesystem::exists(data_analyse_folder)) {
    auto csv_path = data_analyse_folder.append("/ControlResult.csv");
    OutFile.open(csv_path, std::ios::out);
  } else {
    std::filesystem::create_directories(data_analyse_folder);
    auto csv_path = data_analyse_folder.append("/ControlResult.csv");
    OutFile.open(csv_path, std::ios::out);
  }

  for (int i = 0; i < N_sim; i++) {
    int idx_min = path.FindIdxNearstPoint(plant.x_,plant.y_);
    int idx_ref = idx_min + 1;
    double e_dist = path.GetLatErr(idx_ref, plant.x_, plant.y_);
    double e_psi = path.GetPsiErr(idx_ref, plant.psi_);

    delta = 10.0 * e_dist + 5.0 * e_psi;
    delta = fmin(delta, 0.5);
    delta = fmax(delta, -0.5);

    std::cout << e_dist << std::endl;
    plant.Sim(vel, delta, T);

//    store for data_plot
    if (csv_title < 1) {
      OutFile << "t" << ","
              << "x_car" << ","
              << "y_car" << ","
              << "psi_car" << ","
              << "x_path" << ","
              << "y_path" << ","
              << "e_dist" << ","
              << "e_psi" << ","
              << "delta" << ","
              << std::endl;
      csv_title++;
    } else {
      OutFile << plant.t_global_ << ","
              << plant.x_ << ","
              << plant.y_ << ","
              << plant.psi_ << ","
              << path.x_path_[idx_ref]<< ","
              << path.y_path_[idx_ref]<< ","
              << e_dist<< ","
              << e_psi<< ","
              << delta<< ","
              <<std::endl;
    }
  }

  return 0;
}
