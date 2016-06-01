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
    vector<vector<int>> levelOrder(TreeNode* root) {
        auto res = vector<vector<int>>();
        if(!root) return res;
        auto q = queue<TreeNode*>();
        q.push(root);
        while(!q.empty())
        {
            auto size = q.size();
            auto a = vector<int>();
            for(int i =0; i< size; i++)
            {
                auto tempNode= q.front();
                q.pop();
                if(tempNode->left)
                {
                    q.push(tempNode->left);
                }
                if(tempNode->right)
                {
                    q.push(tempNode->right);
                }
                a.emplace_back(tempNode->val);
            }
        res.emplace_back(a);
        }
     return res;
    }
};

//---------------------
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        auto res = vector<vector<int>>();
        if(!root) return res;
        traverse( root, res, 0);
        return res;
    }
    void traverse(TreeNode* node, vector<vector<int>>& res, int depth)
    {
        if(!node)
        {
            return;
        }
        if(res.size() < depth+1)
        {
            res.emplace_back( vector<int>());
        }
        auto& v = res[depth];
        v.emplace_back(node->val);
        traverse(node->left, res, depth +1);
        traverse(node->right, res, depth +1);
    }
};