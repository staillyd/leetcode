#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* delete_duplicates(ListNode* node) {
    ListNode *last = new ListNode(0, node);
    ListNode *ret = last;
    while (node != nullptr) { // 遍历
      bool is_duplicates = false;
      while (node->next != nullptr && node->val == node->next->val) { //删除重复节点
        node->next = node->next->next;
        is_duplicates = true;
      }
      if (is_duplicates) { // 当前节点之前存在重复节点
        node = node->next;
        last->next = node;
      } else {
        last = node;
        node = node->next;
      }
    }
    return ret->next;
  }
};

int main() {
  ListNode* node = new ListNode(1);
  node->append(new ListNode(3));
  node->append(new ListNode(3));
  node->append(new ListNode(4));
  node->append(new ListNode(4));
  node->append(new ListNode(5));
  node->print();

  Solution solution = Solution();
  ListNode* ret = solution.delete_duplicates(node);
  ret->print();
}