#pragma once
#include <iostream>
#include <stack>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}

  void append(ListNode *node) {
    ListNode *now = this;
    while (now->next != nullptr) {
      now = now->next;
    }
    now->next = node;
  }

  void print() {
    ListNode *now(this);
    while (now != nullptr) {
      std::cout << now->val << " ";
      now = now->next;
    }
    std::cout << std::endl;
  }

  void reserve_print() {
    std::stack<int> s;
    ListNode *now(this);
    while (now != nullptr) {
      s.emplace(now->val);
      now = now->next;
    }

    while (!s.empty()) {
      std::cout << s.top() << " ";
      s.pop();
    }
    std::cout << std::endl;
  }
};
