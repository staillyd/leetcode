#include <iostream>
#include <vector>

#include "tree_node.h"

class Solution {
 public:
  void dfs(TreeNode* root, std::string path, std::vector<std::string>& paths) {
    if (!root) {
      return;
    }

    if (path != "") {
      path += "->";
    }
    path += std::to_string(root->val);
    if (!root->left && !root->right) {
      paths.emplace_back(path);
    }

    dfs(root->left, path, paths);
    dfs(root->right, path, paths);

    path = path.substr(0, path.size() - 2 - std::to_string(root->val).size());  // 不pop的话path其实是前序遍历
  }

  std::vector<std::string> binaryTreePaths(TreeNode* root) {
    std::vector<std::string> paths;

    dfs(root, "", paths);

    return paths;
  }
};

int main() {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);

  Solution solution = Solution();
  auto ret = solution.binaryTreePaths(root);
  for (auto str : ret) {
    std::cout << str << std::endl;
  }
}