#include <iostream>
#include <omp.h>

#include "boost/circular_buffer.hpp"

int main(int argc, char const *argv[]) {
  boost::circular_buffer<int> c;
  c.set_capacity(5);

  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  c.push_back(4);
  c.push_back(5);
  c.push_back(6);

  for (int i = 0; i < 5; ++i) {
    std::cout << "i: " << i << " " << c[i] << std::endl;
  }

  std::cout << "---" << std::endl;

#pragma omp parallel for
  for (int i = 0; i < 7; ++i) {
    std::cout << "i: " << i << " " << c.at(i) << std::endl;
  }

  return 0;
}
