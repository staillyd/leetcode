#include <iostream>
#include <vector>

#include "list_node.h"

class Solution {
 public:
  ListNode* merge_2_lists(ListNode* l1, ListNode *l2) {
    ListNode *ret = new ListNode();
    ListNode *last = ret;
    while (l1 != nullptr && l2 != nullptr) {
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

  ListNode* merge_k_lists(std::vector<ListNode*>& lists, int l, int r) {
    if (l >= r) {
      return lists[l];
    }
    int m = l + (r - l) / 2;
    ListNode *l1 = merge_k_lists(lists, 0, m);
    ListNode *l2 = merge_k_lists(lists, m + 1, r);
    return merge_2_lists(l1, l2);
  }

  ListNode* merge_k_lists(std::vector<ListNode*> lists) {
    return merge_k_lists(lists, 0, lists.size() - 1);
  }
};

int main() {
  ListNode* node = new ListNode(3);
  node->append(new ListNode(4));
  node->append(new ListNode(5));
  node->print();

  ListNode* node2 = new ListNode(1);
  node2->append(new ListNode(2));
  node2->append(new ListNode(4));
  node2->print();

  ListNode* node3 = new ListNode(5);
  node3->append(new ListNode(6));
  node3->append(new ListNode(7));
  node3->print();

  std::vector<ListNode *> lists;
  lists.emplace_back(node);
  lists.emplace_back(node2);
  lists.emplace_back(node3);

  Solution solution = Solution();
  ListNode* ret = solution.merge_k_lists(lists);
  ret->print();
}