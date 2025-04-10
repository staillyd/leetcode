#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  int three_sum_closest(std::vector<int>& arr, int target) {
    int ret = -1;
    std::sort(arr.begin(), arr.end());

    float diff = std::numeric_limits<float>::max();
    for (size_t i = 0; i < arr.size(); ++i) {
      if (i > 0 && arr[i] == arr[i - 1]) {  // 去重
        continue;
      }
      size_t l = i + 1, r = arr.size() - 1;
      while (l < r) {
        int sum = arr[i] + arr[l] + arr[r];
        if (std::abs(sum - target) < diff) {
          diff = std::abs(sum - target);
          ret = sum;
        }
        if (sum > 0) {
          --r;
        } else if (sum < 0) {
          ++l;
        } else {
          return sum;
        }
      }
    }
    return ret;
  }
};

int main() {
  std::vector<int> a = {1, 5, 0, 2, 2, 3};

  Solution solution = Solution();
  std::vector<std::vector<int>> ret;
  std::cout << solution.three_sum_closest(a, 4);
}