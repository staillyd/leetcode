#include <iostream>

class Solution {
 public:
  void bubble_sort(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
      bool is_finish = true;
      for (int j = 0; j < len - i - 1; ++j) {
        if (arr[j] > arr[j + 1]) {
          std::swap(arr[j], arr[j + 1]);
          is_finish = false;
        }
      }
      if (is_finish) {
        break;
      }
    }
  }
};

int main() {
  int a[6] = {1, 3, 5, 2, 5, 7};

  Solution solution = Solution();
  solution.bubble_sort(a, 6);

  for (int num : a) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
}