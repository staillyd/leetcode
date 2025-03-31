#include <Eigen/Dense>
#include <iostream>
#include <random>
#include <set>
#include <vector>

std::vector<Eigen::Vector3f> kmeans(const std::vector<Eigen::Vector3f>& points, int k) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, points.size() - 1);

  // 初始化
  std::vector<Eigen::Vector3f> cluster;
  cluster.reserve(k);
  std::set<size_t> random_i;
  while (random_i.size() < k) {
    random_i.emplace(dist(gen));
  }
  for (auto it = random_i.begin(); it != random_i.end(); ++it) {
    cluster.emplace_back(points[*it]);
  }

  int iter_max = 30;
  for (size_t iter = 0; iter < iter_max; ++iter) {
    std::vector<size_t> cluster_idx;
    cluster_idx.reserve(points.size());

    // 点归类
    for (const Eigen::Vector3f& p : points) {
      std::vector<double> distances;
      distances.reserve(k);
      for (size_t i = 0; i < k; ++i) {
        distances.emplace_back((p - cluster[i]).norm());
      }

      cluster_idx.emplace_back(std::distance(distances.begin(), std::min_element(distances.begin(), distances.end())));
    }

    // 重新计算聚类中心点
    for (size_t i = 0; i < k; ++i) {
      int num = 0;
      Eigen::Vector3f sum = Eigen::Vector3f::Zero();
      for (size_t j = 0; j < points.size(); ++j) {
        if (cluster_idx[j] == i) {
          ++num;
          sum += points[j];
        }
      }
      if (num != 0) {
        cluster[i] = sum / num;
      }
    }
  }
  return cluster;
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
  std::vector<Eigen::Vector3f> clusters = kmeans(points, 3);

  for (size_t i = 0; i < clusters.size(); ++i) {
    std::cout << clusters[i].transpose() << std::endl;
  }

  return 0;
}
