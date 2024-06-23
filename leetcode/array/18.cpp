#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  void four_sum(std::vector<int>& arr, int target, std::vector<std::vector<int>>* ret) {
    std::sort(arr.begin(), arr.end());

    for (size_t i = 0; i < arr.size(); ++i) {
      if (i > 0 && arr[i] == arr[i - 1]) {  // 去重
        continue;
      }
      for (size_t j = i + 1; j < arr.size(); ++j) {
        if (j > i + 1 && arr[j] == arr[j - 1]) {  // 去重
          continue;
        }
        size_t l = j + 1, r = arr.size() - 1;
        while (l < r) {
          int sum = arr[i] + arr[j] + arr[l] + arr[r];
          if (sum > target) {
            --r;
          } else if (sum < target) {
            ++l;
          } else {
            std::vector<int> vec = {arr[i], arr[j], arr[l], arr[r]};
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
  }
};

int main() {
  std::vector<int> a = {1, 5, 0, 2, 2, 3};

  Solution solution = Solution();
  std::vector<std::vector<int>> ret;
  solution.four_sum(a, 5, &ret);
  for (const auto& items : ret) {
    for (const auto& item : items) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
}