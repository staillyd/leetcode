#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* swap_pairs(ListNode* node) {
    ListNode *ret = new ListNode(0, node);
    ListNode *last = ret;
    while (node != nullptr) {
      ListNode *next = node->next;
      if (next != nullptr) {
        node->next = next->next;
        next->next = node;
        last->next = next;

        last = node;  // 挪位
        node = node->next; // 挪位
      } else {
        break;
      }
    }
    return ret->next;
  }
};

int main() {
  ListNode* node = new ListNode(3);
  node->append(new ListNode(4));
  node->append(new ListNode(4));
  node->append(new ListNode(5));
  node->print();

  Solution solution = Solution();
  ListNode* ret = solution.swap_pairs(node);
  ret->print();
}