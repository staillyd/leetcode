#include <iostream>
#include <vector>

class Solution {
 public:
  void merge(int arr[], size_t l, size_t m, size_t r) {
    std::vector<int> left(arr + l, arr + m + 1), right(arr + m + 1, arr + r + 1);// 注意m+1, 左闭右开
    size_t i = 0, j = 0;
    for (size_t a = l; a <= r; ++a) {
      if (i < left.size() && j < right.size()) {// 列举各种情况
        arr[a] = left[i] < right[j] ? left[i++] : right[j++]; 
      } else if (i < left.size() && j >= right.size()) {
        arr[a] = left[i++];
      } else {
        arr[a] = right[j++];
      }
    }
  }

  void merge_sort(int arr[], size_t l, size_t r) {
    if (l >= r) {
      return;
    }
    size_t m = (l + r) / 2;
    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
};

int main() {
  int a[6] = {1, 3, 5, 2, 5, 7};

  Solution solution = Solution();
  solution.merge_sort(a, 0, 5);

  for (int num : a) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
}