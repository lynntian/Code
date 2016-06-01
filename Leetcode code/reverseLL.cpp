
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
    ListNode* reverseList(ListNode* head) {
        if(!head) return head;
        auto C = head;
        auto CN = head->next;
        C->next = nullptr;
        while(CN)
        {
            auto CNN = CN->next;
            CN->next = C;
            C = CN;
            CN = CNN;
        }
        return C;
    }
};