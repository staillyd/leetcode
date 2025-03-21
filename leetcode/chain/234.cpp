#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode *reverse(ListNode *node) {
    ListNode * last = nullptr;
    while (node) {
      ListNode * tmp = node->next;
      node->next = last;

      last = node;
      node = tmp;
    }
    return last;
  }

  bool is_palindrome(ListNode* node) {
    ListNode *slow = node, *fast = node->next;
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
    }

    ListNode* second = slow->next;
    slow->next = nullptr;

    ListNode* reverse_node = reverse(second);
    while (node && reverse_node) {
      if (node->val != reverse_node->val) {
        return false;
      }

      node = node->next;
      reverse_node = reverse_node->next;
    }
    return true;
  }
};

int main() {
  ListNode* node = new ListNode(1);
  node->append(new ListNode(2));
  node->print();

  Solution solution = Solution();
  std::cout << solution.is_palindrome(node) << std::endl;
}