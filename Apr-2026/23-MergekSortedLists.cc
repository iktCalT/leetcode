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

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <pstl/glue_algorithm_defs.h>
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
  ListNode *mergeKLists(std::vector<ListNode *> &lists) {
    ListNode *head = nullptr;
    ListNode *current = nullptr;

    // Create a k-member list to store pointers to candidates
    std::vector<ListNode *> candidates =
        lists; // candidates is another name of lists

    // Remove all nullptrs and check if the size is 0
    auto iter = std::remove(candidates.begin(), candidates.end(), nullptr);
    for (auto _ = candidates.end(); _ > iter; _--) {
      candidates.erase(_);
    }
    if (candidates.size() == 0) {
      return head;
    }

    // index of candidate with smallest value
    int min_index;
    bool is_end = true;
    while (true) {
      if (is_end) {
        for (ListNode *c : candidates) {
          if (c->val != INT_MAX) {
            is_end = false;
            break;
          }
        }
        if (is_end) {
          break;
        }
      }

      min_index = 0;
      // we cannot let _ starts with 1, because candidates may have only 1
      // member
      for (size_t _ = 0; _ < candidates.size(); _++) {
        if (candidates[_]->val < candidates[min_index]->val) {
          min_index = _;
        }
      }
      if (head == nullptr) {
        current = head = candidates[min_index];
      } else {
        current->next = candidates[min_index];
        current = current->next;
      }

      if (candidates[min_index]->next == nullptr) {
        // crate a new list node with val = INT_MAX
        candidates[min_index] = new ListNode(INT_MAX);
        is_end = true;
      } else {
        candidates[min_index] = candidates[min_index]->next;
      }
    }
    return head;
  }
};

// Copied from 21-MergeTwoSortedLists.cc
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

  std::vector<ListNode *> lists = {};
  std::cout << "1. ";
  show(demo.mergeKLists(lists));

  lists = {nullptr, nullptr};
  std::cout << "2. ";
  show(demo.mergeKLists(lists));

  lists = {
      new ListNode(1, new ListNode(4, new ListNode(5))),
      new ListNode(1, new ListNode(3, new ListNode(4))),
      new ListNode(5, new ListNode(6)),
      new ListNode(2),
  };
  std::cout << "3. ";
  show(demo.mergeKLists(lists));
}