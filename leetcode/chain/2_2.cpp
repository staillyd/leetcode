#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* kth_to_last(ListNode* node, int k) {
    ListNode *slow = node, *fast = node;
    for (int i = 0; i < k; ++i) {
      fast = fast->next;
    }
    while (fast != nullptr) {
      fast = fast->next;
      slow = slow->next;
    }
    return slow;
  }
};

int main() {
  ListNode* node = new ListNode(1);
  node->append(new ListNode(2));
  node->append(new ListNode(4));
  node->append(new ListNode(3));
  node->append(new ListNode(4));
  node->append(new ListNode(5));
  node->print();

  Solution solution = Solution();
  ListNode* ret = solution.kth_to_last(node, 4);
  std::cout << ret->val << std::endl;
}