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
#include <ostream>
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    ListNode *head, *pm, *pa; // pm: main pointer; pa: assistant pointer

    if (list1 == nullptr) {
      if (list2 == nullptr) {
        return nullptr;
      }
      return list2;
    }
    if (list2 == nullptr) {
      return list1;
    }

    // Use list1 or list2 as head to save space
    if (list1->val <= list2->val) {
      head = list1;
      pm = list1;
      pa = list2;
    } else {
      head = list2;
      pm = list2;
      pa = list1;
    }

    if (pm->next == nullptr) {
      pm->next = pa;
      return head;
    }
    ListNode *tmp;
    while (true) {
      if (pm->next->val <= pa->val) {
        if (pm->next->next == nullptr) {
          pm->next->next = pa;
          break;
        }
        pm = pm->next;
      } else {
        if (pa->next == nullptr) {
          pa->next = pm->next;
          pm->next = pa;
          break;
        }
        tmp = pa->next;
        pa->next = pm->next;
        pm->next = pa;
        pa = tmp;
      }
    }

    return head;
  }
};

void show(ListNode *head) {
  if (head == nullptr) {
    std::cout << std::endl;
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

  ListNode *list1 = new ListNode(1, new ListNode(2, new ListNode(4)));
  ListNode *list2 = new ListNode(1, new ListNode(3, new ListNode(4)));
  show(demo.mergeTwoLists(list1, list2));

  list1 = new ListNode(3, new ListNode(6, new ListNode(9)));
  list2 = new ListNode(1, new ListNode(3, new ListNode(4)));
  show(demo.mergeTwoLists(list1, list2));

  list1 = new ListNode(3);
  list2 = new ListNode(1);
  show(demo.mergeTwoLists(list1, list2));

  list1 = new ListNode(
      -10,
      new ListNode(
          -9,
          new ListNode(
              -6, new ListNode(
                      -4, new ListNode(1, new ListNode(9, new ListNode(9)))))));
  list2 = new ListNode(
      -5, new ListNode(
              -3, new ListNode(
                      0, new ListNode(7, new ListNode(8, new ListNode(8))))));
  show(demo.mergeTwoLists(list1, list2));
}