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
    ListNode* removeElements(ListNode* head, int val) {
        auto node = head;
        ListNode* lastNode = nullptr;
        while(node)
        {
            if(node->val == val)
            {
                if(!lastNode)
                {
                    head = node->next;
                }
                else
                {
                    lastNode->next = node->next;
                }
            }
            else
            {
                lastNode = node;
            }
            node = node->next;
        }
        return head;
    }
};