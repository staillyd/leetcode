#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* reverse_list(ListNode* node) {
    ListNode* last = nullptr;
    ListNode* next;
    while (node != nullptr) {
      next = node->next;
      node->next = last;
      last = node;
      node = next;
    }
    return last;
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
  ListNode* ret = solution.reverse_list(node);
  ret->print();
}