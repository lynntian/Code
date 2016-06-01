/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;

        return binarySplit(head);
    }

    TreeNode* binarySplit(ListNode* node)
    {
        if(!node) return nullptr;
        if(!node->next) return new TreeNode(node->val);

        ListNode* last = nullptr;
        auto first = node; // mid point
        auto second = node;

        if(node->next->next)
        {
            while(first->next && second->next && second->next->next)
            {
                last = first;
                first = first->next;
                second = second->next->next;
            }
        }
        else
        {
            last = first;
            first = first->next;
        }

        if(last) last->next = nullptr;
        auto root = new TreeNode(first->val);

        root->left = binarySplit(node);
        root->right = binarySplit(first->next);

        return root;
    }
};