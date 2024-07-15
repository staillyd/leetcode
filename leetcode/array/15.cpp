#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  void three_sum(std::vector<int>& arr, std::vector<std::vector<int>>* ret) {
    std::sort(arr.begin(), arr.end());

    for (size_t i = 0; i < arr.size(); ++i) {
      if (arr[i] > 0) {  // 题中跟0对比
        break;
      }
      if (i > 0 && arr[i] == arr[i - 1]) {  // 去重
        continue;
      }
      size_t l = i + 1, r = arr.size() - 1;
      while (l < r) {
        int sum = arr[i] + arr[l] + arr[r];
        if (sum > 0) {
          --r;
        } else if (sum < 0) {
          ++l;
        } else {
          std::vector<int> vec = {arr[i], arr[l], arr[r]};
          ret->emplace_back(vec);
          ++l;
          --r;
          while (l < arr.size() && arr[l] == arr[l - 1]) {  // 去重
            ++l;
          }
          while (r > 0 && arr[r] == arr[r + 1]) {  // 去重
            --r;
          }
        }
      }
    }
  }
};

int main() {
  std::vector<int> a = {1, 5, 0, 2, 2, 3};

  Solution solution = Solution();
  std::vector<std::vector<int>> ret;
  solution.three_sum(a, &ret);
}