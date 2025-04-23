#include <algorithm>
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

class Solution {
 public:
  int trap(std::vector<int>& height) {
    // [(持续< 边界-1)_第一次>=当前元素的边界, (持续<= 边界+1)_第一次>当前元素的边界], 当前元素上方承接的雨水
    std::stack<size_t> s;
    int sum = 0;
    // std::vector<std::tuple<size_t, size_t, size_t, int, int, int>> debug;
    for (size_t i = 0; i < height.size(); ++i) {
      while (!s.empty() && height[s.top()] < height[i]) {
        size_t pop_idx = s.top();
        s.pop();
        if (s.empty()) { // 左边没有>当前元素的元素, 接不了雨水
          break;
        }
        size_t l = s.empty() ? 0 : (s.top() + 1) - 1;  // 连续< -1
        size_t r = (i - 1) + 1;                        // 连续<= +1
        // debug.emplace_back(std::make_tuple(pop_idx, l, r, height[pop_idx], height[l], height[r]));
        sum += (std::min(height[l], height[r]) - height[pop_idx]) * (r - l - 1);
      }
      s.push(i);
    }
    // while (!s.empty()) {
    //   size_t pop_idx = s.top();
    //   s.pop();
    //   size_t l = s.empty() ? 0 : (s.top() + 1) - 1;  // 连续< -1
    //   size_t r = height.size() - 1;                  // 连续<=
    //   debug.emplace_back(std::make_tuple(pop_idx, l, r, height[pop_idx], height[l], height[r]));
    // }
    // std::sort(debug.begin(), debug.end());
    // for (auto tmp : debug) {
    //   std::cout << std::get<0>(tmp) << " " << std::get<1>(tmp) << " " << std::get<2>(tmp) << " " << std::get<3>(tmp)
    //             << " " << std::get<4>(tmp) << " " << std::get<5>(tmp) << " " << std::endl;
    // }
    return sum;
  }
};

int main() {
  std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

  Solution solution = Solution();
  std::cout << solution.trap(height);
}