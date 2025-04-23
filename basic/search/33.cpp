#include <iostream>
#include <vector>

class Solution {
 public:
  int search(std::vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
      int m = l + ((r - l) >> 1);
      if (nums[m] == target) {
        return m;
      }
      if (nums[0] <= nums[m]) {                       // 左半区有序
        if (nums[0] <= target && target < nums[m]) {  // target在[0, m]对应区间, 由于nums[m]不等于target可以不写=
          r = m - 1;
        } else {
          l = m + 1;
        }
      } else {  // 右半区有序
        if (nums[m] < target && target <= nums[nums.size() - 1]) {
          l = m + 1;
        } else {
          r = m - 1;
        }
      }
    }
    return -1;
  }
};

int main() {
  std::vector<int> nums = {5, 1, 3};
  Solution solution = Solution();
  std::cout << std::to_string(solution.search(nums, 3));
  return 0;
}