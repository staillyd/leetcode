#include <algorithm>
#include <iostream>

class Solution {
 public:
  void quick_sort(int arr[], int l, int r) {
    if (l >= r) {
      return;
    }
    int p = arr[r];
    int i = l - 1;  // i: <p的最后1个索引, arr[i+1]: >=p的第一个元素
    for (int j = l; j < r; ++j) {
      if (arr[j] < p) {
        std::swap(arr[++i], arr[j]);
      }
    }
    std::swap(arr[i + 1], arr[r]);

    quick_sort(arr, l, i);
    quick_sort(arr, i + 2, r);
  }
};

int main() {
  int a[6] = {1, 3, 5, 2, 5, 7};

  Solution solution = Solution();
  solution.quick_sort(a, 0, 5);

  for (int num : a) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
}