#include <iostream>

class Solution {
 public:
  int binary_search(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) {  // <=
      int m = l + (r - l) / 2;
      if (arr[m] > key) {
        r = m - 1;
      } else if (arr[m] < key) {
        l = m + 1;
      } else {
        if (m + 1 < len && arr[m] != arr[m + 1]) {
          return m;
        }
        l = m + 1;
      }
    }
    return -1;
  }

  int binary_search2(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l < r) {                 // <
      int m = l + (r - l + 1) / 2;  // 向上取整
      if (arr[m] > key) {
        r = m - 1;
      } else {  // 找最后一个<=key, 主要是上一个方法不能应对需要查找元素不相邻的情况
        l = m;
      }
    }
    return (arr[l] == key) ? l : -1;
  }
};

int main() {
  int a[6] = {1, 2, 3, 5, 5, 7};

  Solution solution = Solution();
  int idx = solution.binary_search(a, 6, 5);
  std::cout << "idx: " << idx << std::endl;
  int idx2 = solution.binary_search2(a, 6, 5);
  std::cout << "idx2: " << idx2 << std::endl;
}