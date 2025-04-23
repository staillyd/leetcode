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
        if (sum == 0) {
          std::vector<int> tmp = {arr[i], arr[l], arr[r]};
          ret->emplace_back(tmp);
          while (arr[l] == tmp[1]) { // 去重
            ++l;
          }
          while (arr[r] == tmp[2]) { // 去重
            --r;
          }
        } else if (sum > 0) {
          --r;
        } else if (sum < 0) {
          ++l;
        }
      }
    }
  }
};

int main() {
  std::vector<int> a = {1, -2, 0, 2, 2, -3};

  Solution solution = Solution();
  std::vector<std::vector<int>> ret;
  solution.three_sum(a, &ret);
  for (auto& items : ret) {
    for (auto& item : items) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
}