#include <iostream>

class Solution {
 public:
  int remove_element(int arr[], int len, int key) {
    int new_idx = 0;
    for (int i = 0; i < len; ++i) {
      if (arr[i] != key) {
        arr[new_idx] = arr[i];
        ++new_idx;
      }
    }
    return new_idx;
  }
};

int main() {
  int a[6] = {1, 1, 1, 2, 2, 3};

  Solution solution = Solution();
  int len = solution.remove_element(a, 6, 1);
  for (int i = 0; i < len; ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}