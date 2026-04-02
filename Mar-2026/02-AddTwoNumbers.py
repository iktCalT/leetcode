from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def addTwoNumbers(
        self, l1: Optional[ListNode], l2: Optional[ListNode]
    ) -> Optional[ListNode]:
        if l1:
            if l2:
                # if l1 and l2 are not empty
                l3 = ListNode(l1.val + l2.val)
            else:
                # if l1 is not empty but l2 is empty
                l3 = ListNode(l1.val)
            
            if l3.val < 10:
                l1_next = l1.next
            else:
                l3.val -= 10
                # make sure it won't change original l1
                l1_next = (
                    ListNode(l1.next.val + 1, l1.next.next) # works
                    if type(l1.next) is ListNode
                    else ListNode(1)
                ) 
                
        elif l2:
            # if l1 is empty but l2 is not empty
            l3 = ListNode(l2.val)
            l1_next = None
        else:
            # both l1 and l2 are None
            return None

        l3.next = self.addTwoNumbers(l1_next, l2.next if l2 else None)
        return l3

def show_ll(ll: Optional[ListNode]) -> None:
    if not ll:
        print("None")
    else:
        while type(ll.next) is ListNode:
            print(ll.val, end="")
            ll = ll.next
        print(ll.val)


if __name__ == "__main__":
    demo = Solution()
    l1 = ListNode(2, ListNode(4, ListNode(3)))
    l2 = ListNode(5, ListNode(6, ListNode(4)))
    l3 = demo.addTwoNumbers(l1, l2)
    show_ll(l3)
    
    l1 = ListNode(4)
    l2 = ListNode(6)
    l3 = demo.addTwoNumbers(l1, l2)
    show_ll(l3)