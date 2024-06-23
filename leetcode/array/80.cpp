#include <iostream>

class Solution {
 public:
  int remove_duplicates(int arr[], int len) {
    if (len <= 2) {
      return len;
    }
    int new_idx = 2;
    for (int i = 2; i < len; ++i) {
      if (arr[i] != arr[new_idx - 2]) {
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