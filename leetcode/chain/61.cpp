#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* rotate_right(ListNode* node, size_t k) {
    
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
  ListNode* ret = solution.rotate_right(node, 4);
  ret->print();
}