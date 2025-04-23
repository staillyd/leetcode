#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  std::string longest_common_prefix(std::vector<std::string>& strs) {
    auto min_iter = std::min_element(strs.begin(), strs.end(), [&](const std::string& lhs, const std::string& rhs) {
      return lhs.size() < rhs.size();
    });

    for (int i = 0; i < static_cast<int>((*min_iter).size()); ++i) {
      char s = strs[0][i];
      for (size_t j = 1; j < strs.size(); ++j) {
        if (strs[j][i] != s) {
          return (i - 1 < 0) ? "" : strs[j].substr(0, i);
        }
      }
    }
    return *min_iter;
  }
};

int main() {
  std::vector<std::string> vec;
  vec.emplace_back("floor");
  vec.emplace_back("flower");
  vec.emplace_back("flew");

  Solution solution = Solution();
  std::string pre = solution.longest_common_prefix(vec);

  std::cout << "pre: " << pre << std::endl;
}