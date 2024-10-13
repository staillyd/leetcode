#include <algorithm>
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

class Solution {
 public:
  int trap(std::vector<int>& height) {
    std::stack<size_t> s;
    int sum = 0;
    // std::vector<std::tuple<size_t, size_t, size_t, int, int, int>> debug;
    for (size_t i = 0; i < height.size(); ++i) {
      while (!s.empty() && height[s.top()] < height[i]) {
        size_t pop_idx = s.top();
        s.pop();
        if (s.empty()) {
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