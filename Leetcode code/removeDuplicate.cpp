/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head) return nullptr;
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        auto doubleLast = dummyHead;
        auto lastNumber = head->val;
        auto last = head;
        while(head->next)
        {
            if(head->val == head->next->val) //remove both
            {
                doubleLast->next = head->next->next;
                //head = head->next;
                //lastNumber = head->next->val;
                last = doubleLast;
            }
            else if( lastNumber == head->next->val)
            {
                last->next = head->next->next;
                //head = head->next;
                doubleLast = last;
            }
            else
            {
                doubleLast = last;
                lastNumber = head->next->val;
                last = head->next;
            }
            head = head->next;
        }
        return dummyHead->next; // could be nullptr
    }
};