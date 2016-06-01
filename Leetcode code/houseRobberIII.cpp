/*
Tree dp
pair.second is no rob
pair.first is rob/max val

- rob_root = max(rob_L + rob_R , no_rob_L + no_nob_R + root.val)
- no_rob_root = rob_L + rob_R
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
    int rob(TreeNode* root) {
        return dpTree(root).first;
    }

    pair<int, int> dpTree(TreeNode* root)
    {
        auto res = make_pair(0,0);
        if(!root) return res;
        auto left = dpTree(root->left);
        auto right = dpTree(root->right);
        res.second = left.first + right.first; // no rob
        res.first = max(res.second, left.second + right.second + root->val);

        return res;
    }
};