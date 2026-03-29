#include <stdio.h>

/* Definition for singly-linked list. */
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    // l1->val <= 10, but l2->val < 10
    ListNode *l3;
    ListNode *l1_next;
    if (l1 != nullptr) {
      l3 = l2 != nullptr ? new ListNode(l1->val + l2->val) : l1;
      if (l3->val < 10) {
        l1_next = l1->next;
      } else {
        l3->val -= 10;
        l1_next = l1->next != nullptr
                      ? new ListNode(l1->next->val + 1, l1->next->next)
                      : new ListNode(1);
      }
    } else {
      l1_next = nullptr;
      if (l2 != nullptr) {
        l3 = l2;
      } else {
        return nullptr;
      }
    }

    l3->next = this->addTwoNumbers(l1_next, l2 != nullptr ? l2->next : nullptr);
    return l3;
  }
};

void show_ll(ListNode *ll) {
  if (ll == nullptr) {
    printf("Null");
  } else {
    while (ll->next != nullptr) {
      printf("%d", ll->val);
      ll = ll->next;
    }
    printf("%d\n", ll->val);
  }
}

int main() {
  Solution demo = Solution();
  ListNode *l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
  ListNode *l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
  show_ll(demo.addTwoNumbers(l1, l2));
}