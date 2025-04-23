#include <iostream>

#include "tree_node.h"

class Solution {
 public:
  bool isSymmetric(TreeNode* left, TreeNode* right) {
    if (!left && !right) {
      return true;
    }

    if (left && right && left->val == right->val && isSymmetric(left->left, right->right) &&
        isSymmetric(left->right, right->left)) {
      return true;
    }
    return false;
  }

  bool isSymmetric(TreeNode* root) {
    if (!root) {
      return true;
    }

    return isSymmetric(root->left, root->right);
  }
};

int main() {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);

  Solution solution = Solution();
  auto ret = solution.isSymmetric(root);
  std::cout << ret << std::endl;
}