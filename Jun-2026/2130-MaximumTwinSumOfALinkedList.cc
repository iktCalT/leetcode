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
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  int pairSum(ListNode* head) {
    // get length
    int len = 0;
    for (auto node = head; node != nullptr; node = node->next) {
      ++len;
    }

    int index = 0;
    auto head2 = head->next;
    head->next = nullptr;
    while (index < len / 2 - 1) {
      auto tmp = head;
      head = head2;
      head2 = head2->next;
      head->next = tmp;
      ++index;
    }

    // get answer
    int ans = INT_MIN;
    while (head != nullptr && head2 != nullptr) {
      ans = max(ans, head->val + head2->val);

      head = head->next;
      head2 = head2->next;
    }

    return ans;
  }
};

class Solution0 { // 8ms
public:
  int pairSum(ListNode* head) {
    // add all values to a vector
    vector<int> list;
    auto node = head;
    while (node != nullptr) {
      list.push_back(node->val);
      node = node->next;
    }

    // get max twin sum
    int ans = INT_MIN;
    for (int i = 0; i <= list.size() / 2; ++i) {
      ans = max(ans, list[i] + list[list.size() - 1 - i]);
    }
    return ans;
  }
};