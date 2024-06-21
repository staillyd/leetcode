#include <iostream>

class Solution {
 public:
  void shift_down(int arr[], size_t len, size_t i) {
    size_t idx = i, next_idx = 2 * i + 1;
    while (next_idx < len) {
      // 1. 找到子节点更小的元素, 堆顶最小
      if (next_idx + 1 < len && arr[next_idx + 1] < arr[next_idx]) {
        ++next_idx;
      }
      if (arr[idx] < arr[next_idx]) {
        break;
      }
      // 2. 下沉大的节点
      std::swap(arr[idx], arr[next_idx]);
      idx = next_idx;
      next_idx = 2 * next_idx + 1;
    }
  }

  void heap_sort(int arr[], size_t len) {
    // 1. build sort. 0~len/2为非叶子节点
    for (size_t i = 0; i < len; ++i) {
      shift_down(arr, len, i);
    }
    // 2. 出堆, 为了节省空间, pop堆顶放到最后
    for (size_t i = len - 1; i > 0; --i) {
      std::swap(arr[0], arr[i]);
      shift_down(arr, i, 0);
    }
  }
};

int main() {
  int a[6] = {1, 3, 5, 2, 5, 7};

  Solution solution = Solution();
  solution.heap_sort(a, 6);

  for (int num : a) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
}