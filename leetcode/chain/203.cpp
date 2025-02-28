#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* remove_elements(ListNode* node, int val) {
    ListNode* last = new ListNode(0, node);
    ListNode* ret = last;
    while (node != nullptr) {
      if (node->val == val) {
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
  ListNode* node = new ListNode(4);
  node->append(new ListNode(4));
  node->append(new ListNode(4));
  node->append(new ListNode(3));
  node->append(new ListNode(4));
  node->append(new ListNode(5));
  node->print();

  Solution solution = Solution();
  ListNode* ret = solution.remove_elements(node, 4);
  ret->print();
}