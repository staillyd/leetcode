#include <iostream>
#include <stack>
#include <vector>

#include "tree_node.h"

class Solution {
 public:
  void preorder_traversal(TreeNode* node, std::vector<int>* vec) {
    if (!node) {
      return;
    }

    vec->emplace_back(node->val);
    preorder_traversal(node->left, vec);
    preorder_traversal(node->right, vec);
  }

  std::vector<int> preorder_traversal_1(TreeNode* root) {  // 前序  [根、左、右]
    std::vector<int> vec;

    preorder_traversal(root, &vec);  // 看成只有三个节点（根节点，左子树，右子树）的树，不需要展开，直接调用

    return vec;
  }

  std::vector<int> preorder_traversal(TreeNode* root) {  // 前序  [根、左、右]
    std::vector<int> vec;
    if (!root) {
      return vec;
    }

    std::stack<TreeNode*> s;
    s.emplace(root);

    while (!s.empty()) {  // 非递归 stack 栈顶 [根 - 左右]
      TreeNode* node = s.top();
      vec.emplace_back(node->val);
      s.pop();

      if (node->right) {
        s.push(node->right);
      }
      if (node->left) {
        s.push(node->left);
      }
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
  auto ret = solution.preorder_traversal(root);

  for (const auto& item : ret) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}