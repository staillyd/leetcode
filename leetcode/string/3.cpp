#include <iostream>
#include <unordered_set>

class Solution {
 public:
  int length_of_longest_substring(const std::string& string) {
    // 滑动窗口法(类似快慢指针, 只是慢指针会连续前移)
    // 进入这个队列（窗口）为 abc 满足题目要求，当再进入a，队列变成了abca，这时候不满足要求.将最左侧的元素移除
    std::unordered_set<char> set;
    int max_length = 0;
    int l = 0;
    for (int r = 0; r < static_cast<int>(string.size()); ++r) {
      while (set.find(string[r]) != set.end()) {
        set.erase(string[l]);
        ++l;
      }
      set.emplace(string[r]);
      max_length = std::max(max_length, r - l + 1);
    }
    return max_length;
  }
};

int main() {
  std::string str = "pwwkew";
  // std::string str = "abcabcbb";

  Solution solution = Solution();
  int len = solution.length_of_longest_substring(str);

  std::cout << "max len: " << len << std::endl;
}