#include <eigen3/Eigen/Dense>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

struct Cluster {
  std::vector<size_t> all_indexes;
};

struct Data {
  Data(const Eigen::Vector3f& in_point) : point(in_point) {}

  Eigen::Vector3f point = Eigen::Vector3f::Zero();
  bool is_marked = false;
};

std::vector<size_t> QueryNeighbors(const std::vector<Data>& datas, size_t idx) {
  const float lon_threshold = 3.f, lat_threshold = 0.5f;

  std::vector<size_t> ret;

  Eigen::Vector3f selected_point = datas[idx].point;
  for (size_t i = 0; i < datas.size(); ++i) {
    if (datas[i].is_marked) {
      continue;
    }

    if (std::abs(selected_point.x() - datas[i].point.x()) <= lon_threshold &&
        std::abs(selected_point.y() - datas[i].point.y()) <= lat_threshold) {
      ret.emplace_back(i);
    }
  }

  return ret;
}

std::vector<Cluster> Dbscan(std::vector<Data>& datas) {
  std::vector<Cluster> clusters;

  std::sort(datas.begin(), datas.end(), [](const Data& lhs, const Data& rhs) {
    return lhs.point.norm() < rhs.point.norm();
  });

  for (size_t i = 0; i < datas.size(); ++i) {
    if (datas[i].is_marked) {
      continue;
    }

    Cluster cluster;
    std::queue<size_t> indexes;
    indexes.push(i);
    while (!indexes.empty()) {
      size_t idx = indexes.front();
      indexes.pop();
      if (datas[idx].is_marked) {
        continue;
      }

      datas[idx].is_marked = true;
      cluster.all_indexes.emplace_back(idx);

      std::vector<size_t> neighbors = QueryNeighbors(datas, idx);
      for (const auto& neighbor : neighbors) {
        indexes.push(neighbor);
      }
    }

    clusters.emplace_back(cluster);
  }

  return clusters;
}

int main(int argc, char const* argv[]) {
  std::vector<Data> datas;
  Eigen::Vector3f point1(1, 1, 1);
  Eigen::Vector3f point2(10, 10, 10);
  Eigen::Vector3f point3(11, 11, 11);
  Eigen::Vector3f point4(31, 31, 31);
  Eigen::Vector3f point5(30, 31.3, 31);
  datas.emplace_back(Data(point1));
  datas.emplace_back(Data(point2));
  datas.emplace_back(Data(point3));
  datas.emplace_back(Data(point4));
  datas.emplace_back(Data(point5));
  std::vector<Cluster> clusters = Dbscan(datas);

  for (size_t i = 0; i < clusters.size(); ++i) {
    std::cout << "cluster: " << i << std::endl;
    for (const auto& idx : clusters[i].all_indexes) {
      std::cout << datas[idx].point.transpose() << std::endl;
    }
  }

  return 0;
}
