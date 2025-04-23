#include <iostream>
#include <vector>

class Solution {
 public:
  int coinChange(std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {  // 注意<=
      for (auto c : coins) {
        if (c <= i) {  // 当前单位面值需要<=需要计算的面值
          dp[i] = std::min(dp[i - c] + 1, dp[i]);
        }
      }
    }
    return dp[amount] > amount ? -1 : dp[amount];
  }
};

int main() {
  std::vector<int> coins = {1, 2, 5};
  int amount = 11;

  Solution solution = Solution();
  std::cout << std::to_string(solution.coinChange(coins, amount));
  return 0;
}