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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(!l1 || !l2)
        {
            return l1 ? l1: l2;
        }

        auto res = l1;
        if(l1->val >= l2->val )
        {
            res = l2 ;
            l2 = l2->next;
        }
        else
        {
            l1 = l1->next;
        }
        auto node = res;
        while(l1 && l2)
        {
            if(l1->val >= l2->val)
            {
                node->next = l2;
                node = node->next;
                l2 = l2->next;
            }
            else
            {
                node->next = l1;
                node = node->next;
                l1 = l1->next;
            }
        }
        while(l1 || l2)
        {
            node->next = l1 ? l1 : l2;
            if(l1)
            {
                l1 = l1->next;
            }
            else
            {
                l2 = l2->next;
            }
            node = node->next;
        }
        return res;
    }
};

//Need improve
//-----------------