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

#include <cstddef>
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
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    /*
      Create a queue which is able to store n+1 pointers. Everytime we move
      to the next node, store its location in the queue. When we reaches the
      end of linked list, delete the second node, and link the first and the
      third ones.

      Special case 1: if n equals to size of linked list.
      Special case 2: if n = 1.
     */
    ListNode *pointers[n + 1];
    pointers[0] = pointers[1] = head;

    size_t curr = 1;
    size_t nex;
    while (pointers[curr]->next != nullptr) {
      nex = (curr + 1) % (n + 1);
      pointers[nex] = pointers[curr]->next;
      curr = nex;
    }
    nex = (curr + 1) % (n + 1);

    delete pointers[(nex + 1) % (n + 1)]; // delete nth node from the end
    if (pointers[(nex + 1) % (n + 1)] == head) {
      // If we need to delete the first element of linked list
      if (n == 1)
        head = nullptr;
      else
        head = pointers[(nex + 2) % (n + 1)];
    } else {
      if (n == 1)
        pointers[nex]->next = nullptr; // delete the last node
      else
        pointers[nex]->next = pointers[(nex + 2) % (n + 1)];
    }

    return head;
  }
};

void printLinkedList(ListNode *head) {
  ListNode *curr = head;
  std::cout << "[ ";
  if (curr == nullptr) {
    std::cout << "]" << std::endl;
    return;
  }
  while (curr->next != nullptr) {
    std::cout << curr->val;
    curr = curr->next;
  }
  std::cout << curr->val << " ]" << std::endl;
}

int main() {
  Solution demo = Solution();
  ListNode *head = new ListNode(
      1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
  ListNode *new_ll = demo.removeNthFromEnd(head, 1);
  printLinkedList(new_ll);

  ListNode *head_2 = new ListNode(1);
  ListNode *new_ll_2 = demo.removeNthFromEnd(head_2, 1);
  printLinkedList(new_ll_2);
}