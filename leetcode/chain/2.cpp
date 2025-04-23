#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* add_two_numbers(ListNode* l1, ListNode* l2) {
    ListNode* ret = new ListNode();
    int next_add = 0; // 进位
    ListNode* last = ret; // 上个节点
    while (!(l1 == nullptr && l2 == nullptr && next_add == 0)) { // 在l1 l2 都为nullptr并且进位为0时退出
        int sum = ((l1 != nullptr) ? l1->val : 0) + ((l2 != nullptr) ? l2->val : 0) + next_add;
        last->next = new ListNode(sum % 10);
        next_add = static_cast<int>(sum / 10);

        last = last->next; // 挪位
        l1 = (l1 != nullptr) ? l1->next : l1; // 挪位
        l2 = (l2 != nullptr) ? l2->next : l2; // 挪位
    }
    return ret->next;
  }
};

int main() {
  ListNode l1(6);
  l1.append(new ListNode(5));
  l1.append(new ListNode(3));
  l1.print();
  // l1.reserve_print();

  ListNode l2(4);
  l2.append(new ListNode(2));
  l2.append(new ListNode(4));
  l2.print();
  // l2.reserve_print();

  Solution solution = Solution();
  ListNode* sum = solution.add_two_numbers(&l1, &l2);

  sum->print();
}