#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* reverse_list(ListNode* node) {
    ListNode* last = nullptr;
    ListNode* next = nullptr;
    while (node != nullptr) {
      next = node->next;
      node->next = last;

      last = node;
      node = next;
    }
    return last;
  }

  ListNode* reorder_list(ListNode* node) {
    ListNode *ret = node;
    // 快慢指针求中值
    ListNode *slow = node, *fast = node;
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
    }
    ListNode *right = slow->next;
    slow->next = nullptr;
    // 右半边reverse
    ListNode* second = reverse_list(right);
    // 拼接
    while (node && second) {
      ListNode *node_next = node->next;
      ListNode *second_next = second->next;

      node->next = second;
      second->next = node_next;

      node = node_next;
      second = second_next;
    }

    return ret;
  }
};

int main() {
  ListNode* node = new ListNode(3);
  node->append(new ListNode(4));
  node->append(new ListNode(5));
  node->append(new ListNode(2));
  node->append(new ListNode(4));
  node->append(new ListNode(6));
  node->append(new ListNode(7));
  node->print();

  Solution solution = Solution();
  ListNode* ret = solution.reorder_list(node);
  ret->print();
}