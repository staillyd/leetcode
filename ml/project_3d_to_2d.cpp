#include <eigen3/Eigen/Dense>
#include <iostream>

bool project_3d_to_2d(const Eigen::Affine3d& Tr_world_to_camera, const Eigen::Matrix3d& K_camera,
                      const float image_width, const float image_height, const Eigen::Vector3d& point,
                      Eigen::Vector2d* point2d) {
  Eigen::Vector3d point_camera = Tr_world_to_camera * point;
  if (point_camera.z() < 0) {
    return false;
  }

  Eigen::Vector3d uvs = K_camera * point_camera;
  uvs = uvs / uvs.z();

  if (uvs.x() < 0 || uvs.x() >= image_width || uvs.y() < 0 || uvs.y() >= image_height) {
    return false;
  }

  (*point2d) = uvs.head(2);
  return true;
}

int main(int argc, char const* argv[]) {
  Eigen::Affine3d Tr_world_to_camera;
  Tr_world_to_camera.linear() << -0.00668226, -0.99997168, 0.00346173, 0.03742761, -0.00370949, -0.99929246, 0.999277,
      -0.00654796, 0.03745133;
  Tr_world_to_camera.translation() << -0.03510065, 1.01522599, -2.0873683;
  Eigen::Matrix3d K_camera;
  K_camera << 7.362225e+03, 0.000000e+00, 1.913020e+03, 0.000000e+00, 7.359546e+03, 1.096820e+03, 0.000000e+00,
      0.000000e+00, 1.000000e+00;
  Eigen::Vector3d point = {2.61727142e+01, 7.87588894e-01, -3.59000000e-01};

  Eigen::Vector2d point2d = Eigen::Vector2d::Zero();
  bool sucess = project_3d_to_2d(Tr_world_to_camera, K_camera, 3840.f, 2160.f, point, &point2d);

  std::cout << "sucess: " << sucess << " point2d: " << point2d.transpose() << std::endl;

  return 0;
}
