/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <cstdio>
#include <iostream>
#include <string>
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *swapPairs(ListNode *head) {
    ListNode *curr, *tmp = nullptr;

    // If more than 1 node, swap the first two
    if (head != nullptr && head->next != nullptr) {
      curr = head;
      head = head->next;
    }

    while (curr != nullptr && curr->next != nullptr) {
      // change entry node
      if (tmp != nullptr) {
        tmp->next = curr->next;
      }
      // modify pointers
      tmp = curr;
      curr = curr->next;
      // swap next
      tmp->next = curr->next;
      curr->next = tmp;
      // next
      // be careful, not curr = curr->next, because we've changed curr->next
      curr = tmp->next;
    }

    return head;
  }

  
  ListNode *swapPairs_2(ListNode *head) {
    ListNode *curr, *tmp = nullptr;

    // If more than 1 node, swap the first two
    if (head != nullptr && head->next != nullptr) {
      curr = head;
      head = head->next;
    }

    while (curr != nullptr && curr->next != nullptr) {
      // change entry node
      if (tmp != nullptr) {
        tmp->next->next = curr->next;
      }
      // modify pointers
      tmp = curr->next;
      // swap next
      curr->next = tmp->next;
      tmp->next = curr;
      // next
      // be careful, not curr = curr->next, because we've changed curr->next
      curr = curr->next;
    }

    return head;
  }
};

void show(ListNode *head) {
  if (head == nullptr) {
    std::cout << std::endl;
    return;
  }

  ListNode *p = head;
  while (true) {
    std::cout << p->val << " ";
    if (p->next == nullptr) {
      break;
    }
    p = p->next;
  }
  std::cout << std::endl;
}

int main() {
  Solution demo = Solution();

  ListNode *head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
  show(demo.swapPairs(head));
}