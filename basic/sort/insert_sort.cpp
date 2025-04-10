#include <iostream>

class Solution {
 public:
  void insert_sort(int arr[], int len) {
    if (len <= 1) {
      return;
    }
    for (int i = 1; i < len; ++i) {
      for (int j = i - 1; j >= 0 && arr[j + 1] < arr[j]; --j) {
        std::swap(arr[j + 1], arr[j]);
      }
    }
  }
};

int main() {
  int a[6] = {1, 3, 5, 2, 5, 7};

  Solution solution = Solution();
  solution.insert_sort(a, 6);

  for (int num : a) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
}