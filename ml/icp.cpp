#include <ceres/ceres.h>
#include <ceres/rotation.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/point_cloud.h>
#include <pcl/registration/icp.h>

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
#include <sophus/so3.hpp>
#include <utility>
#include <vector>

// Ceres自动求导 只支持Ceres内部的变量
struct Point2PointFactor {
  Point2PointFactor(const Eigen::Vector3d& origin_point, const Eigen::Vector3d& new_point)
      : _origin_point(origin_point), _new_point(new_point) {}

  // 输入: 待求参数   输出: 残差
  template <typename T>
  bool operator()(const T* pose_6, T* residual) const {
    // Eigen::Affine3d trans; // 不能从ceres类型转换成 double等类型, 给matrix赋值
    T p[3];
    T p_origin[3];
    p_origin[0] = T(_origin_point.x());
    p_origin[1] = T(_origin_point.y());
    p_origin[2] = T(_origin_point.z());
    ceres::AngleAxisRotatePoint(pose_6, p_origin, p);  // 输入的是3维旋转向量
    p[0] += pose_6[3];
    p[1] += pose_6[4];
    p[2] += pose_6[5];

    residual[0] = p[0] - T(_new_point[0]);
    residual[1] = p[1] - T(_new_point[1]);
    residual[2] = p[2] - T(_new_point[2]);
    return true;
  }

  // 输入数据
  const Eigen::Vector3d _origin_point;
  const Eigen::Vector3d _new_point;
};

Eigen::Matrix3d get_Tr(float roll, float pitch, float yaw) {
  Eigen::Matrix3d R;
  Eigen::Matrix3d R_yaw;
  R_yaw << std::cos(yaw), -std::sin(yaw), 0, std::sin(yaw), std::cos(yaw), 0, 0, 0, 1;
  Eigen::Matrix3d R_pitch;
  R_pitch << std::cos(pitch), 0, std::sin(pitch), 0, 1, 0, -std::sin(pitch), 0, std::cos(pitch);
  Eigen::Matrix3d R_roll;
  R_roll << 1, 0, 0, 0, std::cos(roll), -std::sin(roll), 0, std::sin(roll), std::cos(roll);
  R = R_yaw * R_pitch * R_roll;
  return R;
}

bool icp(const std::vector<Eigen::Vector3d>& origin_points, const std::vector<Eigen::Vector3d>& new_points,
         Eigen::Affine3d* Tr_origin_to_new) {
  size_t max_iter = 50;
  pcl::PointCloud<pcl::PointXYZ>::Ptr pc_new(new pcl::PointCloud<pcl::PointXYZ>());
  pc_new->points.resize(new_points.size());
  for (size_t i = 0; i < new_points.size(); ++i) {
    pc_new->points[i].x = new_points[i].x();
    pc_new->points[i].y = new_points[i].y();
    pc_new->points[i].z = new_points[i].z();
  }
  pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
  kdtree.setInputCloud(pc_new);

  // 粗配准
  Eigen::Affine3d tr_origin_to_new = Eigen::Affine3d::Identity();
  Eigen::MatrixXd new_points_maxtrix(new_points.size(), 3);
  for (size_t i = 0; i < new_points.size(); ++i) {
    new_points_maxtrix.row(i) = new_points[i];
  }
  Eigen::Vector3d new_center = new_points_maxtrix.colwise().mean();
  Eigen::MatrixXd origin_points_maxtrix(origin_points.size(), 3);
  for (size_t i = 0; i < origin_points.size(); ++i) {
    origin_points_maxtrix.row(i) = origin_points[i];
  }
  Eigen::Vector3d origin_center = origin_points_maxtrix.colwise().mean();
  tr_origin_to_new.translation() = new_center - origin_center;  // x_new - x_origin
  tr_origin_to_new.linear() = get_Tr(40 * M_PI / 180, 50 * M_PI / 180, 55 * M_PI / 180);

  for (size_t iter = 0; iter < max_iter; ++iter) {
    // 1. 数据关联
    std::vector<std::pair<int, int>> match_pairs;
    for (size_t i = 0; i < origin_points.size(); ++i) {
      Eigen::Vector3d trans_new = tr_origin_to_new * origin_points[i];
      std::vector<int> match_idxes(1);
      std::vector<float> match_distance(1);
      kdtree.nearestKSearch(pcl::PointXYZ(trans_new.x(), trans_new.y(), trans_new.z()), 1, match_idxes, match_distance);
      if (match_distance[0] < 100) {
        match_pairs.emplace_back(std::make_pair(static_cast<int>(i), match_idxes[0]));
      }
    }

    // 2. 估计位姿
    if (match_pairs.empty()) {
      std::cout << "empty" << std::endl;
      return false;
    }

    Eigen::MatrixXd matched_origin_points(match_pairs.size(), 3), matched_new_points(match_pairs.size(), 3);
    for (size_t i = 0; i < match_pairs.size(); ++i) {
      matched_origin_points.row(i) = origin_points[match_pairs[i].first];
      matched_new_points.row(i) = new_points[match_pairs[i].second];
    }

    // origin^T * new -> R=V*U^T;     new^T * origin -> R = U * V^T
    auto icp_svd = [&]() {
      Eigen::Vector3d matched_origin_center = matched_origin_points.colwise().mean();
      Eigen::Vector3d matched_new_center = matched_new_points.colwise().mean();
      Eigen::Matrix3d H = (matched_origin_points.rowwise() - matched_origin_center.transpose()).transpose() *
                          (matched_new_points.rowwise() - matched_new_center.transpose());

      Eigen::JacobiSVD<Eigen::MatrixXd> svd;
      svd.compute(H, Eigen::ComputeThinU | Eigen::ComputeThinV);
      Eigen::Matrix3d R = svd.matrixV() * svd.matrixU().transpose();
      Eigen::Vector3d t = matched_new_center - R * matched_origin_center;

      tr_origin_to_new.linear() = R;
      tr_origin_to_new.translation() = t;
    };

    auto icp_gaussnewton = [&]() {
      size_t max_iter_gauss = 30;
      for (size_t i = 0; i < max_iter_gauss; ++i) {
        Eigen::MatrixXd jacobi(3, 6);
        Eigen::Vector3d err = Eigen::Vector3d::Zero();

        Eigen::MatrixXd H = Eigen::MatrixXd::Zero(6, 6);
        Eigen::VectorXd b = Eigen::VectorXd::Zero(6);
        for (int j = 0; j < matched_origin_points.rows(); ++j) {  // rows
          // err和jacobi正负对应
          err = tr_origin_to_new * matched_origin_points.block<1, 3>(j, 0).transpose() -
                matched_new_points.block<1, 3>(j, 0).transpose();  // 矩阵乘的时候注意维度
          jacobi.block<3, 3>(0, 0) =
              -tr_origin_to_new.linear() * Sophus::SO3<double>::hat(matched_origin_points.block<1, 3>(j, 0));
          jacobi.block<3, 3>(0, 3) = Eigen::Matrix3d::Identity();

          H += jacobi.transpose() * jacobi;
          b += -jacobi.transpose() * err;
        }

        Eigen::VectorXd delta_x = H.inverse() * b;
        // Eigen::HouseholderQR<Eigen::MatrixXd> qr(H);
        // Eigen::VectorXd delta_x = qr.solve(b);  // computes H^-1 * b

        // rank1相乘方式
        // Eigen::MatrixXd jacobis(3 * matched_origin_points.rows(), 6);
        // Eigen::MatrixXd errs(3, matched_origin_points.rows());
        // for (int j = 0; j < matched_origin_points.rows(); ++j) {
        //   err.block<3, 1>(j, 0) =
        //         tr_origin_to_new * matched_origin_points.block<1, 3>(j, 0).transpose() -
        //         matched_new_points.block<1, 3>(j, 0).transpose();  // 矩阵乘的时候注意维度

        //   jacobis.block<3, 3>(j * matched_origin_points.rows(), 0) =
        //       -tr_origin_to_new.linear() * Sophus::SO3<double>::hat(matched_origin_points.block<1, 3>(j, 0));
        //   jacobis.block<3, 3>(j * matched_origin_points.rows(), 3) = Eigen::Matrix3d::Identity();
        // }
        // Eigen::VectorXd delta_x = (jacobis.transpose() * jacobis).inverse() * (-jacobis.transpose() * err);

        tr_origin_to_new.linear() =
            tr_origin_to_new.linear().eval() * Sophus::SO3<double>::exp(delta_x.head(3)).matrix();
        tr_origin_to_new.translation() = tr_origin_to_new.translation().eval() + delta_x.tail(3);
      }
    };

    auto icp_ceres = [&]() {
      ceres::Problem problem;
      // Eigen::Vector3d rpy = tr_origin_to_new.linear().matrix().eulerAngles(2, 1, 0);
      Eigen::AngleAxisd rot_vec(tr_origin_to_new.linear().matrix());
      Eigen::Vector3d rot_vec3 = rot_vec.angle() * rot_vec.axis();
      double pose_6[6] = {rot_vec3[0],                          // 旋转向量, 不是roll
                          rot_vec3[1],                          // 旋转向量, pitch
                          rot_vec3[2],                          // 旋转向量, yaw
                          tr_origin_to_new.matrix()(0, 3),      // t1
                          tr_origin_to_new.matrix()(1, 3),      // t2
                          tr_origin_to_new.matrix()(2, 3)};     // t3
      for (int j = 0; j < matched_origin_points.rows(); ++j) {  // rows
        problem.AddResidualBlock(  // ceres输入、输出参数都是数组形式, 计算残差时都用ceres内部的变量, 函数
            new ceres::AutoDiffCostFunction<Point2PointFactor, 3, 6>(  // 输出残差维度, 输入待估计参数的维度
                new Point2PointFactor(matched_origin_points.block<1, 3>(j, 0),  // 输入数据
                                      matched_new_points.block<1, 3>(j, 0))),   // cost_function
            nullptr,                                                            // 核函数
            pose_6);                                                            // 输入待估计参数
      }

      ceres::Solver::Options options;
      options.linear_solver_type = ceres::DENSE_QR;  // 增量方程求解方式
      options.minimizer_progress_to_stdout = true;   // 输出到cout

      ceres::Solver::Summary summary;  // 日志
      ceres::Solve(options, &problem, &summary);

      // std::cout << summary.BriefReport() << std::endl;

      // Eigen::AngleAxisd roll(pose_6[0], Eigen::Vector3d::UnitX());
      // Eigen::AngleAxisd pitch(pose_6[1], Eigen::Vector3d::UnitY());
      // Eigen::AngleAxisd yaw(pose_6[2], Eigen::Vector3d::UnitZ());
      // Eigen::Quaternion<double> q = yaw * pitch * roll;  // 右乘
      // tr_origin_to_new.linear() = q.matrix();

      Eigen::Vector3d R_vec = {pose_6[0], pose_6[1], pose_6[2]};  // 旋转向量
      Eigen::Vector3d R_vec_normlize = R_vec.normalized();
      Eigen::AngleAxisd rot_estimate;  // eigen形式的旋转向量
      rot_estimate.angle() = R_vec[0] / R_vec_normlize[0];
      rot_estimate.axis() = R_vec_normlize;
      Eigen::Matrix3d R_estimate = rot_estimate.matrix();

      tr_origin_to_new.linear() = R_estimate;
      tr_origin_to_new.translation() << pose_6[3], pose_6[4], pose_6[5];
    };

    // icp_svd();
    // icp_gaussnewton();
    icp_ceres();
  }
  *Tr_origin_to_new = tr_origin_to_new;
  return true;
}

void pcl_icp(const std::vector<Eigen::Vector3d>& origin_points, const std::vector<Eigen::Vector3d>& new_points,
             Eigen::Affine3d* Tr_origin_to_new) {
  Eigen::Affine3d tr_origin_to_new = Eigen::Affine3d::Identity();
  Eigen::MatrixXd new_points_maxtrix(new_points.size(), 3);
  for (size_t i = 0; i < new_points.size(); ++i) {
    new_points_maxtrix.row(i) = new_points[i];
  }
  Eigen::Vector3d new_center = new_points_maxtrix.colwise().mean();
  Eigen::MatrixXd origin_points_maxtrix(origin_points.size(), 3);
  for (size_t i = 0; i < origin_points.size(); ++i) {
    origin_points_maxtrix.row(i) = origin_points[i];
  }
  Eigen::Vector3d origin_center = origin_points_maxtrix.colwise().mean();
  tr_origin_to_new.translation() = new_center - origin_center;  // x_new - x_origin
  tr_origin_to_new.linear() = get_Tr(40 * M_PI / 180, 50 * M_PI / 180, 55 * M_PI / 180);

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_origin(new pcl::PointCloud<pcl::PointXYZ>());
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_new(new pcl::PointCloud<pcl::PointXYZ>());
  cloud_origin->points.resize(origin_points.size());
  cloud_new->points.resize(new_points.size());
  for (size_t i = 0; i < origin_points.size(); ++i) {
    Eigen::Vector3d trans_origin_point = tr_origin_to_new * origin_points[i];
    cloud_origin->points[i].x = trans_origin_point.x();
    cloud_origin->points[i].y = trans_origin_point.y();
    cloud_origin->points[i].z = trans_origin_point.z();
  }
  for (size_t i = 0; i < new_points.size(); ++i) {
    cloud_new->points[i].x = new_points[i].x();
    cloud_new->points[i].y = new_points[i].y();
    cloud_new->points[i].z = new_points[i].z();
  }

  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
  icp.setInputCloud(cloud_origin);
  icp.setInputTarget(cloud_new);
  pcl::PointCloud<pcl::PointXYZ> cloud_final;
  icp.align(cloud_final);  // 进行配准
  if (icp.hasConverged()) {
    Tr_origin_to_new->matrix() = icp.getFinalTransformation().cast<double>() * tr_origin_to_new.matrix();
  }
}

int main(int argc, char const* argv[]) {
  cv::RNG rng;

  std::vector<Eigen::Vector3d> origin_points;
  for (size_t i = 0; i < 60; ++i) {
    origin_points.emplace_back(
        Eigen::Vector3d(rng.uniform(-10.f, 10.f), rng.uniform(-5.f, 5.f), rng.uniform(-3.f, 3.f)));
  }

  Eigen::Affine3d Tr_origin_to_new;
  float roll = 30 * M_PI / 180, pitch = 60 * M_PI / 180, yaw = 45 * M_PI / 180;
  Tr_origin_to_new.linear() = get_Tr(roll, pitch, yaw);
  Tr_origin_to_new.translation() << 3, 4, 1;

  std::vector<Eigen::Vector3d> new_points;
  for (size_t i = 0; i < 60; ++i) {
    new_points.emplace_back(Tr_origin_to_new * origin_points[i]);
  }

  Eigen::Affine3d Tr_estimate = Eigen::Affine3d::Identity();
  icp(origin_points, new_points, &Tr_estimate);
  // pcl_icp(origin_points, new_points, &Tr_estimate);

  std::cout << "gt: R: " << Tr_origin_to_new.rotation() << " t: " << Tr_origin_to_new.translation() << std::endl;
  std::cout << "estimate: R: " << Tr_estimate.rotation() << " t: " << Tr_estimate.translation() << std::endl;
  std::cout << "diff: R: " << (Tr_origin_to_new.rotation() - Tr_estimate.rotation())
            << " t: " << (Tr_origin_to_new.translation() - Tr_estimate.translation()) << std::endl;

  return 0;
}
