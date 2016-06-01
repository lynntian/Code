Inorder traversal: recursive:
    void inorderRec(TreeNode* r, vector<int>& ret)
    {
        if(!r) return;
        inorderRec(r->left, ret);
        ret.push_back(r->val);
        inorderRec(r->right, ret);
    }

Inorder, iterative: USE STACK
    //iterative
    vector<int> inorderTraversal(TreeNode* root) {
        auto res = vector<int>();
        auto s = stack<TreeNode*>();
        auto node = root;
        while(!s.empty() || node)
        {
            if(node)
            {
                s.push(node);
                node = node->left;
            }
            else
            {
                node = s.top();
                s.pop();
                res.push_back(node->val);
                node = node->right;
            }
        }
        return res;
    }