#include <iostream>
#include <vector>

class Solution {
 public:
  void dfs(const size_t start, const std::vector<int>& nums) {
    for (size_t i = start; i < nums.size(); ++i) {
      path.emplace_back(nums[i]);
      ret.emplace_back(path);
      dfs(i + 1, nums);
      path.pop_back();
    }
  }

  std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
    dfs(0, nums);

    return ret;
  }

 private:
  std::vector<int> path;
  std::vector<std::vector<int>> ret = {{}};
};

int main() {
  Solution solution = Solution();

  std::vector<int> nums = {1, 2, 3};
  std::vector<std::vector<int>> ret;
  ret = solution.subsets(nums);
  for (const auto& subset : ret) {
    for (const auto& item : subset) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
}