#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  void four_sum(std::vector<int>& arr, int target, std::vector<std::vector<int>>* ret) {
    std::sort(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); ++i) {
      if (arr[i] == arr[i - 1] && i != 0) { // 去重
        continue;
      }
      for (int j = i + 1; j < arr.size(); ++j) {
        if (arr[j] == arr[j - 1] && j != i + 1) { // 去重
          continue;
        }
        int k = j + 1, l = arr.size() - 1;
        while (k < l) {
          int sum = arr[i] + arr[j] + arr[k] + arr[l];
          if (sum == target) {
            std::vector<int> tmp = {arr[i], arr[j], arr[k], arr[l]};
            ret->emplace_back(tmp);
            while (arr[k] == tmp[2]) { // 去重
              ++k;
            }
            while (arr[l] == tmp[3]) { // 去重
              --l;
            }
          } else if (sum < target) {
            ++k;
          } else {
            --l;
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