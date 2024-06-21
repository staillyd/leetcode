#include <iostream>

class Solution {
 public:
  void shell_sort(int arr[], int len) {
    if (len <= 1) {
      return;
    }
    for (int gap = len / 2; gap >= 1; gap = gap / 2) {
      for (int i = gap; i < len; i = i + gap) {
        for (int j = i - gap; j >= 0 && arr[j + gap] < arr[j]; j = j - gap) {
          std::swap(arr[j + gap], arr[j]);
        }
      }
    }
  }
};

int main() {
  int a[6] = {1, 3, 5, 2, 5, 7};

  Solution solution = Solution();
  solution.shell_sort(a, 6);

  for (int num : a) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
}