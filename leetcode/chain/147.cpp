#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* insertion_sort_list(ListNode* node) {
    ListNode *ret = new ListNode(0, node);
    ListNode *last = node; // 修改链表顺序需要last
    ListNode *cur = node->next;

    while (cur != nullptr) {
      if (last->val <= cur->val) {
        cur = cur->next;
        last = last->next;
      } else {
        ListNode *find = ret->next;
        ListNode *last_find = ret; // 修改链表顺序需要last
        while (find->val <= cur->val) {
          last_find = find;
          find = find->next;
        }

        last->next = cur->next;
        cur->next = find;
        last_find->next = cur;
        
        cur = last->next;
      }
    }
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
  ListNode* ret = solution.insertion_sort_list(node);
  ret->print();
}