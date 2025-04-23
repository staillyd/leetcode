#include <iostream>
#include <vector>

class Solution {
 public:
  int numSquares(int n) {
    std::vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
      int minn = i;
      std::cout << "start i: " << std::to_string(i);
      for (int j = 1; j * j <= i; ++j) {
        minn = std::min(minn, dp[i - j * j] + 1);
        std::cout << " compare idx: " << i - j * j << " minn: " << minn;
      }
      std::cout << std::endl;
      dp[i] = minn;
    }
    return dp[n];
  }
};

int main() {
  Solution solution = Solution();
  std::cout << solution.numSquares(5);
  return 0;
}