#include <algorithm>
#include <iostream>

class Solution {
 public:
  void select_sort(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
      auto min_iter = std::min_element(arr + i, arr + len);
      std::swap(arr[i], arr[min_iter - arr]);
    }
  }
};

int main() {
  int a[6] = {1, 3, 5, 2, 5, 7};

  Solution solution = Solution();
  solution.select_sort(a, 6);

  for (int num : a) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
}