#include <eigen3/Eigen/Dense>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

std::vector<Eigen::Vector3f> kmeans(const std::vector<Eigen::Vector3f>& points,
                                    int k) {
  std::vector<Eigen::Vector3f> ret;
  ret.reserve(k);

  // 初始化
  cv::RNG rng;
  for (int i = 0; i < k; ++i) {
    int idx = rng.uniform(0, points.size() - 1);
    ret.emplace_back(points[idx]);
  }

  for (int iter = 0; iter < 2; ++iter) {
    std::vector<size_t> cluster_idxs;
    cluster_idxs.reserve(points.size());
    for (const Eigen::Vector3f& point : points) {
      std::vector<float> dist;
      dist.reserve(k);
      for (int i = 0; i < k; ++i) {
        dist.emplace_back((point - ret[i]).norm());
      }
      cluster_idxs.emplace_back(std::distance(
          dist.begin(), std::min_element(dist.begin(), dist.end())));
    }

    for (size_t i = 0; i < ret.size(); ++i) {
      int num = 0;
      Eigen::Vector3f cluster = Eigen::Vector3f::Zero();
      for (size_t point_i = 0; point_i < points.size(); ++point_i) {
        if (cluster_idxs[point_i] == i) {
          ++num;
          cluster += points[point_i];
        }
      }
      cluster = cluster / num;
      ret[i] = cluster;
    }
  }

  return ret;
}

int main(int argc, char const* argv[]) {
  std::vector<Eigen::Vector3f> points;
  Eigen::Vector3f point1(1, 1, 1);
  Eigen::Vector3f point2(10, 10, 10);
  Eigen::Vector3f point3(11, 11, 11);
  Eigen::Vector3f point4(31, 31, 31);
  Eigen::Vector3f point5(31, 31, 31);
  points.emplace_back(point1);
  points.emplace_back(point2);
  points.emplace_back(point3);
  points.emplace_back(point4);
  points.emplace_back(point5);
  std::vector<Eigen::Vector3f> clusters = kmeans(points, 2);

  for (size_t i = 0; i < clusters.size(); ++i) {
    std::cout << clusters[i].transpose() << std::endl;
  }

  return 0;
}
