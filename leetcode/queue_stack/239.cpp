#include <iostream>
#include <vector>
#include <queue>

class Solution {
 public:
  std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    std::vector<int> ret;
    std::deque<size_t> q;

    // 类似单调栈, 这里是单调减双向队列
    for (size_t i = 0; i < k; ++i) {
      while (!q.empty() && nums[q.back()] <= nums[i]) {
        q.pop_back();
      }
      q.emplace_back(i);
    }
    ret.emplace_back(nums[q.front()]); // 队首是当前双向队列最大元素

    for (size_t i = k; i < nums.size(); ++i) {
      while (!q.empty() && nums[q.back()] <= nums[i]) {
        q.pop_back();
      }
      q.emplace_back(i);

      while (q.front() <= i - k) {// 双向队列队首元素不满足窗口[i-k+1, i]时, pop
        q.pop_front();
      }
      ret.emplace_back(nums[q.front()]);
    }

    return ret;
  }

  std::vector<int> maxSlidingWindow_pirorqueue(std::vector<int>& nums, int k) {
    std::vector<int> ret;
    std::priority_queue<std::pair<int, int>> q;
    for (size_t i = 0; i < k; ++i) {
      q.emplace(nums[i], i);
    }
    ret.emplace_back(q.top().first);

    for (size_t i = k; i < nums.size(); ++i) {
      q.emplace(nums[i], i);
      while (q.top().second <= i - k) { // 优先队列栈顶元素不满足窗口[i-k+1, i]时, pop
        q.pop();
      }
      ret.emplace_back(q.top().first);
    }
    return ret;
  }

  std::vector<int> maxSlidingWindow_origin(std::vector<int>& nums, int k) {
    std::vector<int> ret;
    std::vector<int> tmp = {};
    for (int i = 0; i < nums.size() - k + 1; ++i) {
      tmp.assign(nums.begin() + i, nums.begin() + i + k);
      ret.emplace_back(*std::max_element(tmp.begin(), tmp.end()));
    }
    return ret;
  }
};

int main() {
  std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};

  Solution solution = Solution();
  std::vector<int> ret = solution.maxSlidingWindow(nums, 3);
  for (auto item : ret) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}