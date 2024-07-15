#include <iostream>

struct Point {
  Point(float in_x, float in_y, float in_val) : x(in_x), y(in_y), val(in_val) {};

  float x;
  float y;
  float val;
};


float bilinear_interpolation(float x1, float x2, float v1, float v2, float x) {
  float ratio = (x - x1) / (x2 - x1);
  float v = (1 - ratio) * v1 + ratio * v2;
  return v;
}

int main(int argc, char const *argv[]) {
  Point p1(0., 0., 0.);
  Point p2(10, 0, 10.);
  Point p3(0., 10., 10.);
  Point p4(10., 10., 100.);

  Point p(5, 5, 0);
  float vy_1 = bilinear_interpolation(p1.y, p3.y, p1.val, p3.val, p.y);
  float vy_2 = bilinear_interpolation(p2.y, p4.y, p2.val, p4.val, p.y);
  p.val = bilinear_interpolation(p1.x, p2.x, vy_1, vy_2, p.x);

  std::cout << vy_1 << " " << vy_2 << " " << p.val << std::endl;

  return 0;
}
