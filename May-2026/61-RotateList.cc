#include <algorithm>
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
  ListNode *rotateRight(ListNode *head, int k) {
    if (head == nullptr || k == 0) {
      return head;
    }

    int len = getLength(head);
    ListNode *nodes[min(k + 1, len)];
    int cur = 0;
    nodes[cur] = head;
    while (true) {
      ListNode *node = nodes[cur]->next;
      if (node == nullptr)
        break;
      cur = (cur + 1) % (k + 1);
      nodes[cur] = node;
    }
    nodes[cur]->next = head;
    if (cur == len - 1) {
      // Linked list length: cur+1
      k = k % (cur + 1);
      nodes[cur - k]->next = nullptr;
      head = nodes[(cur - k + 1) % (cur + 1)];
    } else {
      cur = (cur + 1) % (k + 1);
      nodes[cur]->next = nullptr;
      head = nodes[(cur + 1) % (k + 1)];
    }
    return head;
  }

private:
  inline int getLength(ListNode *head) {
    int count = 0;
    while (head != nullptr) {
      count++;
      head = head->next;
    }
    return count;
  }
};