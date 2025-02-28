#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Solution {
 public:
  int solve(const std::string& string) {
    std::unordered_set<char> set;
    int l = 0, max_len = 0;
    for (int i = 0; i < string.size(); ++i) {
      while (set.find(string[i]) != set.end()) {
        set.erase(string[l]);
        ++l;
      }
      set.emplace(string[i]);
      max_len = std::max(max_len, i - l + 1);
    }
    return max_len;
  }
};

int main() {
  std::string str = "pwwkew";
  // std::string str = "abcabcbb";

  Solution solution = Solution();
  int len = solution.solve(str);

  std::cout << "max len: " << len << std::endl;
}
