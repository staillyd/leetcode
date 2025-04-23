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

  ListNode* reverse_list(ListNode* node, int start, int end) {
    int index = 0;
    ListNode *ret = new ListNode(0, node);
    ListNode *last = ret, *last_start = nullptr;
    ListNode *start_node = nullptr, *end_next_node = nullptr;
    while (node != nullptr) {
      ++index;
      if (index == start) {
        last_start = last;
        start_node = node;
      } else if (index == end) {
        end_next_node = node->next;
        node->next = nullptr; // 关键
        break;
      }

      last = node;
      node = node->next;
    }
    
    ListNode* reverse = reverse_list(start_node);
    last_start->next = reverse;
    start_node->next = end_next_node;

    return ret->next;
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
  ListNode* ret = solution.reverse_list(node, 1, 2);
  ret->print();
}