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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        auto ioSize = inorder.size();

        if(preorder.size()== 0 || ioSize == 0)
        {
            return nullptr;
        }
        auto p = 0;

        return build(preorder, inorder, 0, ioSize, p);
    }

    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int a, int b, int& p)
    {
        if(b == a) return nullptr;

        auto root = new TreeNode(preorder[p]);
        auto f = find(inorder.begin() + a, inorder.end() + b, root->val) - inorder.begin();
        p++;
        root->left = build(preorder, inorder, a, f, p);
        root->right = build( preorder, inorder, f+1, b, p);
        return root;

    }
};