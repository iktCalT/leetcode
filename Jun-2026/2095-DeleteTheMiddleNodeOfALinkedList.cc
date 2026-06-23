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

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution { // 0ms
public:
  ListNode* deleteMiddle(ListNode* head) {
    // Two pointers, one jump 1 node per step
    // the other jump 2 node per step
    ListNode* slow = head;
    ListNode* fast = head->next ? head->next->next : nullptr;

    if (fast == nullptr) { // only 1 or 2 node(s)
      if (head->next == nullptr) {
        return nullptr;
      } else {
        head->next = nullptr;
        return head;
      }
    }

    while (fast && fast->next) {
      fast = fast->next ? fast->next->next : nullptr;
      slow = slow->next;
    }
    
    slow->next = slow->next->next;
    return head;
  }
};

class Solution2 { // 4ms
public:
  ListNode* deleteMiddle(ListNode* head) {
    if (head->next == nullptr) return nullptr; // only one node
    
    // Two pointers, one jump 1 node per step
    // the other jump 2 node per step
    ListNode* slow = head;
    ListNode* fast = head->next ? head->next->next : nullptr;

    while (true) {
      if (fast == nullptr || fast->next == nullptr) {
        slow->next = slow->next ? slow->next->next : nullptr;
        return head;
      }
      fast = fast->next ? fast->next->next : nullptr;
      slow = slow->next;
    }
    return nullptr;
  }
};

class Solution1 { // 3ms
public:
  ListNode* deleteMiddle(ListNode* head) {
    // Get size
    int size = 0;
    for (ListNode* node = head; node != nullptr; node = node->next) {
      ++size;
    }

    // to prevent if statement, create a new node
    head = new ListNode(0, head);
    
    ListNode* prev = head; // pos = 0
    for (int i = 0; i < size / 2; ++i) {
      prev = prev->next;
    } // the previous node of the one to be deleted

    ListNode* node = prev->next;
    prev->next = node->next ? node->next : nullptr;
    auto p = head->next;
    delete head;

    return p;
  }
};

class Solution0 { // 1ms
public:
  ListNode* deleteMiddle(ListNode* head) {
    // Get size
    int size = 0;
    for (ListNode* node = head; node != nullptr; node = node->next) {
      ++size;
    }

    int pos = size / 2;
    if (pos <= 0) { // no previous nodes
      // ListNode* node = head;
      head = head->next;
      // delete node; // Leetcode don't allow me to delete
      return head;
    }
    
    ListNode* prev = head; // pos = 0
    for (int i = 0; i < pos - 1; ++i) {
      prev = prev->next;
    } // the previous node of the one to be deleted

    ListNode* node = prev->next;
    prev->next = node->next ? node->next : nullptr;
    // delete node;

    return head;
  }
};