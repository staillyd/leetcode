#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#include "tree_node.h"

class Solution {
 public:
  void postorderTraversal(TreeNode* node, std::vector<int>* vec) {
    if (!node) {
      return;
    }

    postorderTraversal(node->left, vec);
    postorderTraversal(node->right, vec);
    vec->emplace_back(node->val);
  }

  std::vector<int> postorderTraversal_1(TreeNode* root) {  // 后序  [左、右、根]
    std::vector<int> vec;

    postorderTraversal(root, &vec);  // 看成只有三个节点（根节点，左子树，右子树）的树，不需要展开，直接调用

    return vec;
  }

  std::vector<int> postorderTraversal_2(TreeNode* root) {  // 后序  栈顶 [左-右、根]
    std::vector<int> vec;
    if (!root) {
      return vec;
    }

    std::stack<TreeNode*> s;
    s.push(root);

    while (!s.empty()) {  // 栈顶 [根-右、左] 前序便历, 再reverse
      TreeNode* node = s.top();
      s.pop();
      vec.emplace_back(node->val);

      if (node->left) {
        s.emplace(node->left);
      }
      if (node->right) {
        s.emplace(node->right);
      }
    }

    std::reverse(vec.begin(), vec.end());

    return vec;
  }

  std::vector<int> postorderTraversal(TreeNode* root) {  // 后序  栈顶 [左-右、根]
    std::vector<int> vec;
    if (!root) {
      return vec;
    }

    std::stack<TreeNode*> s;
    TreeNode* last_pop = nullptr;
    while (root || !s.empty()) {  // 非递归 stack 栈顶 [左右根], 在左子树、右子树访问完之前, 当前节点不能提前出栈
      while (root) {  // 找到最左侧节点, 过程中push节点
        s.emplace(root);
        root = root->left;
      }

      TreeNode* node = s.top();
      if (node->right && last_pop != node->right) {  // 右子树访问完之前, last_pop: 保证右子树没访问过, 不然会重复遍历
        root = node->right;
      } else {  // 当前节点
        s.pop();
        vec.emplace_back(node->val);
        last_pop = node;  // 注意
        root = nullptr;   // 注意, 当前节点pop时, 不再走左右节点, 也是为了不重复遍历
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
  auto ret = solution.postorderTraversal(root);

  for (const auto& item : ret) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}