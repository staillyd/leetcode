#include <eigen3/Eigen/Dense>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void get_line_param_by_2points(const Eigen::Vector2d &point1, const Eigen::Vector2d &point2,
                               Eigen::Vector3d *line_param) {
  (*line_param) << point2.y() - point1.y(), point1.x() - point2.x(), -point1.x() * point2.y() + point2.x() * point1.y();
}

double get_distance_to_line(const Eigen::Vector2d &point, const Eigen::Vector3d &line_param) {
  Eigen::Vector3d point_homogeneouse = {point.x(), point.y(), 1};
  double distance = line_param.dot(point_homogeneouse) / line_param.head(2).norm();
  return distance;
}

double get_y_value_of_line(const Eigen::Vector3d &line_param, const double x) {
  double y = (-line_param(2) - line_param(0) * x) / line_param(1);
  return y;
}

void ransac(const std::vector<Eigen::Vector2d> &datas, Eigen::Vector3d *line_param) {
  cv::RNG rng;
  int max_iter = 5;
  float distance_threshold = 0.5;
  int inner_cout = 0, max_inner_count = 0;
  Eigen::Vector3d best_line_param, iter_line_param;
  for (int iter = 0; iter < max_iter; ++iter) {
    size_t idx_1 = rng.uniform(0, datas.size());
    size_t idx_2 = rng.uniform(0, datas.size());
    inner_cout = 0;
    get_line_param_by_2points(datas[idx_1], datas[idx_2], &iter_line_param);
    for (const Eigen::Vector2d &point : datas) {
      double distance = get_distance_to_line(point, iter_line_param);
      if (distance <= distance_threshold) {
        ++inner_cout;
      }
    }
    if (max_inner_count < inner_cout) {
      best_line_param = iter_line_param;
    }
  }
  *line_param = best_line_param.normalized();
}

int main(int argc, char const *argv[]) {
  Eigen::Vector3d line_param_gt = {1, 1, 3};
  line_param_gt.normalize();
  std::cout << "line_param_gt: " << line_param_gt.transpose() << std::endl;

  cv::RNG rng;
  std::vector<Eigen::Vector2d> vec_gt, vec;
  size_t size = 5;
  vec_gt.reserve(size);
  vec.reserve(size);
  for (size_t i = 0; i < size; ++i) {
    Eigen::Vector2d tmp(i, get_y_value_of_line(line_param_gt, i));
    vec_gt.emplace_back(tmp);
    tmp += Eigen::Vector2d(rng.uniform(0.0, 0.5), rng.uniform(0.0, 0.5));
    vec.emplace_back(tmp);
  }

  std::cout << "input data: " << std::endl;
  for (size_t i = 0; i < size; ++i) {
    std::cout << vec[i].transpose() << std::endl;
  }

  Eigen::Vector3d line_param;
  ransac(vec, &line_param);
  std::cout << line_param.transpose() << std::endl;
  return 0;
}
