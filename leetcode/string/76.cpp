#include <iostream>
#include <numeric>
#include <unordered_map>

class Solution {
 public:
  std::string min_window(const std::string& s, const std::string& t) {
    std::string ret = "";
    size_t l = 0, min_w = std::numeric_limits<size_t>::max();

    size_t remain_count = t.size();                     // 滑动窗口中t字符还需要的个数
    std::unordered_map<char, size_t> remain_map_count;  // 滑动窗口中t字符还需要的 map 个数
    for (const auto& item : t) {
      if (remain_map_count.find(item) == remain_map_count.end()) {
        remain_map_count[item] = 0;
      }
      ++remain_map_count[item];
    }

    for (size_t r = 0; r < s.size(); ++r) {
      if (remain_map_count.find(s[r]) != remain_map_count.end()) {       // 如果当前字符在t里存在
        while (remain_map_count[s[r]] == 0 ||                            // 不符合条件时, 连续抛出慢指针
               remain_map_count.find(s[l]) == remain_map_count.end()) {  // 直到慢指针字符在t中
          if (remain_map_count.find(s[l]) != remain_map_count.end()) {
            ++remain_map_count[s[l]];
            ++remain_count;
          }
          ++l;
        }

        --remain_map_count[s[r]];  // 当前字符计数--
        --remain_count;

        if (remain_count == 0) {  // 如果刚好满足字符个数要求
          if (r - l + 1 < min_w) {
            min_w = r - l + 1;
            ret = s.substr(l, r + 1);
          }
        }
      }
    }

    return ret;
  }
};

int main() {
  std::string s = "ADOBECODEBANC";
  std::string t = "ABC";

  Solution solution = Solution();
  std::string sub = solution.min_window(s, t);

  std::cout << "sub: " << sub << std::endl;
}