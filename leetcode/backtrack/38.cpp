#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  void dfs(std::string goods, std::vector<int>* visited) {
    if (path.size() == goods.size()) {
      ret.emplace_back(path);
    }

    for (size_t i = 0; i < goods.size(); ++i) {
      if ((*visited)[i] == 1) {
        continue;
      }

      if (i > 0 && goods[i] == goods[i - 1] && (*visited)[i - 1] == 0) {
        continue;
      }

      path += goods[i];
      (*visited)[i] = 1;

      dfs(goods, visited);

      path = path.substr(0, path.size() - 1);
      (*visited)[i] = 0;
    }
  }

  std::vector<std::string> goodsOrder(std::string goods) {
    std::sort(goods.begin(), goods.end());
    std::vector<int> visited(goods.size(), 0);

    dfs(goods, &visited);
    return ret;
  }

 private:
  std::string path = "";
  std::vector<std::string> ret;
};

int main() {
  Solution solution = Solution();

  std::vector<std::string> ret;
  ret = solution.goodsOrder("aax");
  for (const auto& item : ret) {
    std::cout << item << " " << std::endl;
  }
}