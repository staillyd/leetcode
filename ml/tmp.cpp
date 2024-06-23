#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<size_t> x;
  x.emplace_back(1);

  std::vector<size_t> y = {2, 3, 4, 5};

  x.insert(x.begin(), y.begin(), y.end());

  for (const auto item: x) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  return 0;
}
