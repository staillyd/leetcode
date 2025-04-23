#include <iostream>
#include <stack>
#include <vector>

#include "tree_node.h"

class Solution {
 public:
  void inorderTraversal(TreeNode* node, std::vector<int>* vec) {
    if (!node) {
      return;
    }

    inorderTraversal(node->left, vec);
    vec->emplace_back(node->val);
    inorderTraversal(node->right, vec);
  }

  std::vector<int> inorderTraversal_1(TreeNode* root) {  // 中序  [左、根、右]
    std::vector<int> vec;

    inorderTraversal(root, &vec);  // 看成只有三个节点（根节点，左子树，右子树）的树，不需要展开，直接调用

    return vec;
  }

  std::vector<int> inorderTraversal(TreeNode* root) {  // 中序  [左、根、右]
    std::vector<int> vec;
    if (!root) {
      return vec;
    }

    std::stack<TreeNode*> s;
    while (root || !s.empty()) {  // 非递归 stack 栈顶 [左根右], 在左子树访问之前, 当前节点不能提前出栈
      while (root) {              // 找到最左侧节点, 过程中push节点
        s.emplace(root);
        root = root->left;
      }

      TreeNode* node = s.top();  // 左子树访问完, pop
      s.pop();
      vec.emplace_back(node->val);
      root = node->right;  // 往右遍历
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
  auto ret = solution.inorderTraversal(root);

  for (const auto& item : ret) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}