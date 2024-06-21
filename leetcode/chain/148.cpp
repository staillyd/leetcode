#include <iostream>

#include "list_node.h"

class Solution {
 public:
  ListNode* merge_2_list(ListNode* l1, ListNode * l2) {
    ListNode *ret = new ListNode();
    ListNode *last = ret;
    while (l1 && l2) {
      if (l1->val <= l2->val) {
        last->next = l1;
        l1 = l1->next;
      } else {
        last->next = l2;
        l2 = l2->next;
      }
      last = last->next;
    }

    last->next = l1 ? l1 : l2;
    return ret->next;
  }

  ListNode* merge_sort_list(ListNode* node) {
    if (!(node && node->next)) { // nullptr或单个节点 return
      return node;
    }

    // 找中间位置
    ListNode *slow = node;
    ListNode *fast = node->next; //很关键. 如果是node, 那么两个节点时, 当前轮次跟下一轮次参数一样, 不会return
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    ListNode *second = slow->next;
    slow->next = nullptr; //关键

    ListNode* l1 = merge_sort_list(node);
    ListNode* l2 = merge_sort_list(second);
    return merge_2_list(l1, l2);
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
  ListNode* ret = solution.merge_sort_list(node);
  ret->print();
}