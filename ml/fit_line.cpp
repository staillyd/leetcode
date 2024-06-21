#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

// ref: https://eigen.tuxfamily.org/dox/TopicTemplateKeyword.html
template <typename S>
double get_distance_to_line(const Eigen::Matrix<S, 3, 1>& line_param, const Eigen::Matrix<S, 2, 1>& point) {
    double distance = (line_param.template head<2>().dot(point) + line_param[2])/ line_param.template head<2>().norm();
    return distance;
}

double get_y_value_of_line(const Eigen::Vector3d& line_param, const double x) {
    double y = (-line_param(2) - line_param(0) * x) / line_param(1);
    return y;
}

template <typename S>
bool fit_line_svd(const std::vector<Eigen::Matrix<S, 2, 1>>& data, Eigen::Matrix<S, 3, 1> *line_param) {
    Eigen::MatrixXd A(data.size(), 3);
    for (size_t i = 0; i < data.size(); ++i) {
        A.row(i).head(2) = data[i];
        A.row(i)(2) = 1.0f;
    }

    Eigen::JacobiSVD<Eigen::MatrixXd> svd;
    svd.compute(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
    (*line_param) = svd.matrixV().col(2);

    int count = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        float err = get_distance_to_line((*line_param), data[i]);
        if (err * err > 1) {
            ++count;
        }
    }
    std::cout << "count: " << count << std::endl;
    return true;
}

template <typename S>
bool fit_line_svd2(const std::vector<Eigen::Matrix<S, 2, 1>>& data, Eigen::Matrix<S, 2, 1> *p, Eigen::Matrix<S, 2, 1> *dir) {
    Eigen::MatrixXd A(data.size(), 2);
    for (size_t i = 0; i < data.size(); ++i) {
        A.row(i) = data[i];
    }
    (*p) = A.colwise().mean();
    std::cout << "mean p:" << (*p).transpose() << std::endl;
    A.rowwise() -= (*p).transpose();

    Eigen::JacobiSVD<Eigen::MatrixXd> svd;
    svd.compute(A, Eigen::ComputeThinV);
    (*dir) = svd.matrixV().col(0);

    return true;
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
        tmp += Eigen::Vector2d(rng.uniform(0.0, 0.01), rng.uniform(0.0, 0.01));
        vec.emplace_back(tmp);
    }

    std::cout << "input data: " << std::endl;
    for (size_t i = 0; i < size; ++i) {
        std::cout << vec[i].transpose() << std::endl;
    }

    Eigen::Vector3d line_param = Eigen::Vector3d::Zero();
    fit_line_svd(vec, &line_param);

    std::cout << "fit_line_svd param: " << line_param.transpose() << std::endl;
    std::cout << "fit data: " << std::endl;
    for (size_t i = 0; i < size; ++i) {
        std::cout << vec[i](0) << ", " << get_y_value_of_line(line_param, vec[i][0]) << std::endl;
    }

    Eigen::Vector2d p_gt(vec_gt[0]);
    Eigen::Vector2d dir_gt(vec_gt[1][0] - vec_gt[0][0], vec_gt[1][1] - vec_gt[0][1]);
    dir_gt.normalize();
    std::cout << "p gt: " << p_gt.transpose() << " dir gt: " << dir_gt.transpose() << std::endl;

    Eigen::Vector2d p = Eigen::Vector2d::Zero();
    Eigen::Vector2d dir = Eigen::Vector2d::Zero();
    fit_line_svd2(vec, &p, &dir);
    std::cout << "p: " << p.transpose() << " dir: " << dir.transpose() << std::endl;

    return 0;
}
