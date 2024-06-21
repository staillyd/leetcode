#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* delete_duplicates(ListNode* node) {
    ListNode *ret = node;
    while (node != nullptr) { // 遍历
      while (node->next != nullptr && node->val == node->next->val) { // 去重
        node->next = node->next->next;
      }
      node = node->next;
    }
    return ret;
  }
};

int main() {
  ListNode* node = new ListNode(3);
  node->append(new ListNode(4));
  node->append(new ListNode(4));
  node->append(new ListNode(5));
  node->print();

  Solution solution = Solution();
  ListNode* ret = solution.delete_duplicates(node);
  ret->print();
}