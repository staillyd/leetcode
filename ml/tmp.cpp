#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  Eigen::Affine3d tr = Eigen::Affine3d::Identity();
  Eigen::Matrix3d m = Eigen::Matrix3d::Identity();
  Eigen::Vector3d v = Eigen::Vector3d::Zero();

  std::cout << m(0, 0) << std::endl;
  std::cout << v[0] << std::endl;

  return 0;
}
