#include <Eigen/Dense>
#include <iostream>
#include <random>
#include <vector>

double get_y_value_of_line(const Eigen::Vector3d& param, double x) { return (-param[0] * x - param[2]) / param[1]; }

void get_line_param_by_2_points(const Eigen::Vector2d& p1, const Eigen::Vector2d& p2, Eigen::Vector3d* param) {
  (*param) << p1.y() - p2.y(), -p1.x() + p2.x(), p1.x() * p2.y() - p2.x() * p1.y();
}

double get_distance_from_point_to_line(const Eigen::Vector3d& param, const Eigen::Vector2d& p) {
  Eigen::Vector3d p_1 = {p.x(), p.y(), 1};
  return param.dot(p_1) / param.head(2).norm();
}

void ransac(std::vector<Eigen::Vector2d> vec, Eigen::Vector3d* line_param) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, vec.size() - 1);

  int iter = 0, iter_max = 10;
  double distance_threshold = 0.3;
  int inner_count = 0, max_inner_count = 0;
  Eigen::Vector3d best_line_param, iter_line_param;
  while (iter < iter_max) {
    int idx1 = dist(gen), idx2 = dist(gen);
    while (idx1 == idx2) {
      idx1 = dist(gen);
      idx2 = dist(gen);
    }

    Eigen::Vector2d p1 = vec[idx1], p2 = vec[idx2];
    get_line_param_by_2_points(p1, p2, &iter_line_param);

    inner_count = 0;
    for (const Eigen::Vector2d& p : vec) {
      double distance = get_distance_from_point_to_line(iter_line_param, p);
      if (distance < distance_threshold) {
        ++inner_count;
      }
    }

    if (inner_count > max_inner_count) {
      max_inner_count = inner_count;
      best_line_param = iter_line_param;
    }
    ++iter;
  }
  *line_param = best_line_param.normalized();
}

int main(int argc, char const* argv[]) {
  Eigen::Vector3d line_param_gt = {1, 1, 3};
  line_param_gt.normalize();
  std::cout << "line_param_gt: " << line_param_gt.transpose() << std::endl;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(0.0, 0.5);

  std::vector<Eigen::Vector2d> vec_gt, vec;
  size_t size = 15;
  vec_gt.reserve(size);
  vec.reserve(size);
  for (size_t i = 0; i < size; ++i) {
    Eigen::Vector2d tmp(i, get_y_value_of_line(line_param_gt, i));
    vec_gt.emplace_back(tmp);
    tmp += Eigen::Vector2d(dist(gen), dist(gen));
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
