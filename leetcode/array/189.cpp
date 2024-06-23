#include <iostream>

class Solution {
 public:
  void rotate(int arr[], int len, int k) {
    k = k % 10;
    // 反转: 不新增内存
    for (int i = 0; i < len / 2; ++i) {
      std::swap(arr[i], arr[len - 1 - i]);
    }
    for (int i = 0; i < k / 2; ++i) {
      std::swap(arr[i], arr[k - 1 - i]);
    }
    for (int i = k; i < k + (len - k) / 2; ++i) {
      std::swap(arr[i], arr[len - 1 - i + k]);
    }
  }
};

int main() {
  int a[7] = {1, 2, 3, 4, 5, 6, 7};

  Solution solution = Solution();
  solution.rotate(a, 7, 3);
  for (int i = 0; i < 7; ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}