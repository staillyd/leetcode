#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<int> merge(std::vector<int> vec1, std::vector<int> vec2) {
    std::vector<int> ret(vec1.size() + vec2.size());
    size_t l = 0, r = 0;
    for (size_t i = 0; i < ret.size(); ++i) {
      if (l < vec1.size() && r < vec2.size()) {
        if (vec1[l] < vec2[r]) {
          ret[i] = vec1[l];
          ++l;
        } else {
          ret[i] = vec2[r];
          ++r;
        }
      } else if (l >= vec1.size() && r < vec2.size()) {
        ret[i] = vec2[r];
        ++r;
      } else if (l < vec1.size() && r >= vec2.size()) {
        ret[i] = vec1[l];
        ++l;
      }
    }
    return ret;
  }
};

int main() {
  int a[6] = {1, 1, 1, 2, 2, 3};

  Solution solution = Solution();
}