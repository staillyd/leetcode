#include <iostream>
#include <queue>
#include <vector>

#include "tree_node.h"

class Solution {
 public:
  std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> vec;
    if (!root) {
      return vec;
    }

    std::queue<TreeNode*> q;
    q.emplace(root);
    while (!q.empty()) {
      size_t level_size = q.size();
      std::vector<int> inner_vec;
      for (size_t i = 0; i < level_size; ++i) {  // 当前层的个数, 遍历当前层
        TreeNode* node = q.front();
        q.pop();
        inner_vec.emplace_back(node->val);

        if (node->left) {
          q.emplace(node->left);
        }
        if (node->right) {
          q.emplace(node->right);
        }
      }

      vec.emplace_back(inner_vec);
    }

    return vec;
  }
};

int main() {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);

  Solution solution = Solution();
  auto ret = solution.levelOrder(root);

  for (const auto& items : ret) {
    for (const auto& item : items) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}