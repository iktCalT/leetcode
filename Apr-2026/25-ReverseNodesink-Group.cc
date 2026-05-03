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

#include <iostream>
#include <tuple>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (k <= 1 || head == nullptr) {
      return head;
    }

    ListNode *subhead = head, *subtail = new ListNode(0, head);
    head = nullptr; // Make sure head can be changed only once.

    do {
      std::tie(subhead, subtail) = reverseSubGroup(subtail, k);
      if (head == nullptr) {
        head = subhead;
      }
    } while (subhead != subtail);
    // If subhead == new_subhead, the number of remaining nodes is less than k

    return head;
  }

private:
  std::tuple<ListNode *, ListNode *> reverseSubGroup(ListNode *lasttail,
                                                     const int k) {
    // First value in returned tuple: new_head
    // Second value in returned tuple: new_tail
    // If new_head == new_tail -> reverse failed (not enough nodes)

    std::vector<ListNode *> ptrs;
    if (k <= 1 || lasttail == nullptr || lasttail->next == nullptr) {
      return {lasttail, lasttail};
    } else if (k == 2) {
      if (lasttail->next->next == nullptr) {
        return {lasttail, lasttail};
      }
      ptrs = {lasttail->next, lasttail->next->next, lasttail->next->next->next};
      ptrs[1]->next = ptrs[0];
      ptrs[0]->next = ptrs[2];
      lasttail->next = ptrs[1];
      return {ptrs[1], ptrs[0]};
    }

    // --- Initialization ---
    ListNode *tmphead = lasttail->next;
    if (tmphead == nullptr || tmphead->next == nullptr) {
      // 0 or 1 node left
      return {lasttail, lasttail};
    } else if (tmphead->next->next == nullptr) {
      // 2 nodes left, k > 2
      return {lasttail, lasttail};
    } else {
      // We need 3 pointers to make sure we won't lose access to the following
      // nodes
      ptrs = {tmphead, tmphead->next, tmphead->next->next};
    }

    // --- Reverse nodes in subgroup ---
    int cur = 0;
    for (; cur < k - 2; cur++) {
      // Change and recover should be faster than verify and change
      // Only ptrs[(cur + 2) % 3] could be nullptr
      if (ptrs[(cur + 2) % 3] == nullptr) {
        // --- Recover ---
        recover(ptrs, cur);
        return {lasttail, lasttail};
      }

      // --- Change ---
      ptrs[(cur + 1) % 3]->next = ptrs[cur % 3];
      ptrs[cur % 3] = ptrs[(cur + 2) % 3]->next;
    }

    // Now, ptrs[cur % 3] and ptrs[(cur + 1) % 3] are the last two nodes
    // of current subgroup, while ptrs[(cur + 2) % 3] is the head of next
    // subgroup
    ptrs[(cur + 1) % 3]->next = ptrs[cur % 3];
    lasttail->next = ptrs[(cur + 1) % 3];
    tmphead->next = ptrs[(cur + 2) % 3];

    return {ptrs[(cur + 1) % 3], tmphead};
  }

  void recover(std::vector<ListNode *> &ptrs, int cur) {
    while (cur != 0) {
      ptrs[(cur + 1) % 3]->next = ptrs[(cur + 2) % 3];
      ptrs[(cur + 2) % 3] = ptrs[cur % 3]->next;
      cur--;
    }
    ptrs[(cur + 1) % 3]->next = ptrs[(cur + 2) % 3];
    return;
  }
};

void show(ListNode *head) {
  if (head == nullptr) {
    std::cout << std::endl;
    return;
  }

  ListNode *p = head;
  while (p != nullptr) {
    std::cout << p->val << " ";
    p = p->next;
  }
  std::cout << std::endl;
}

int main() {
  Solution demo = Solution();

  ListNode *head = new ListNode(
      1,
      new ListNode(
          2,
          new ListNode(
              3, new ListNode(
                     4, new ListNode(5, new ListNode(6, new ListNode(7)))))));
  show(demo.reverseKGroup(head, 1));
  head = new ListNode(
      1,
      new ListNode(
          2,
          new ListNode(
              3, new ListNode(
                     4, new ListNode(5, new ListNode(6, new ListNode(7)))))));
  show(demo.reverseKGroup(head, 2));
  head = new ListNode(
      1,
      new ListNode(
          2,
          new ListNode(
              3, new ListNode(
                     4, new ListNode(5, new ListNode(6, new ListNode(7)))))));
  show(demo.reverseKGroup(head, 3));
  head = new ListNode(
      1,
      new ListNode(
          2,
          new ListNode(
              3, new ListNode(
                     4, new ListNode(5, new ListNode(6, new ListNode(7)))))));
  show(demo.reverseKGroup(head, 4));
}