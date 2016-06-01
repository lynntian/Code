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
    int kthSmallest(TreeNode* root, int k) {
        res = 0;
        counter = 0;
        inorder(root,k);
        return res;
    }

    void inorder(TreeNode* r, int k)
    {
        if(!r) return;

        inorder(r->left, k);
        counter++;
        if(counter == k)
        {
            res = r->val;
            return;
        }
        inorder(r->right, k);
    }
private:
    int res;
    int counter;

};