#include <iostream>
#include <set>

class Solution {
 public:
  std::string reverse_vowels(std::string& str) {
    std::set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    size_t l = 0, r = str.size() - 1;
    while (l < r) {
      while (l < r && vowels.find(str[l]) == vowels.end()) {
        ++l;
      }
      while (l < r && vowels.find(str[r]) == vowels.end()) {
        --r;
      }
      if (l < r) {
        std::swap(str[l], str[r]);
        ++l;
        --r;
      } else {
        break;
      }
    }
    return str;
  }
};

int main() {
  std::string str = "leetcode";

  Solution solution = Solution();
  std::string reverse = solution.reverse_vowels(str);

  std::cout << "reverse: " << reverse << std::endl;
}