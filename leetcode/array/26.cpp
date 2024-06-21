#include <iostream>

class Solution {
 public:
  int remove_duplicates(int arr[], int len) {
    int new_idx = 1;
    for (int i = 1; i < len; ++i) {
      if (arr[i] != arr[new_idx - 1]) {
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
  int len = solution.remove_duplicates(a, 6);
  for (int i = 0; i < len; ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}