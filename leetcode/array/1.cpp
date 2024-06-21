#include <iostream>
#include <unordered_map>

class Solution {
 public:
  std::pair<int, int> two_sum(int arr[], int len, int key) {
    std::unordered_map<int, int> num_to_idx;
    for (int i = 0; i < len; ++i) {
      if (num_to_idx.find(key - arr[i]) != num_to_idx.end()) {
        return std::make_pair(i, num_to_idx[key - arr[i]]);
      }
      num_to_idx[arr[i]] = i;
    }
    return std::make_pair(-1, -1);
  }
};

int main() {
  int a[6] = {1, 5, 0, 2, 2, 3};

  Solution solution = Solution();
  const auto& pair = solution.two_sum(a, 6, 7);
  std::cout << "repeat num: " << pair.first << ", " << pair.second << std::endl;
}