//https://leetcode.com/discuss/74474/ac-solution-code
public ListNode getIntersectionNode(ListNode headA, ListNode headB) 
{ 
    if (headA == null || headB == null) return null; 
    ListNode curA = headA, curB = headB; 
    while (curA != curB) 
    {
         curA = (curA == null) ? headB : curA.next; 
         curB = (curB == null) ? headA : curB.next; } 
         return curA; 
    }
}