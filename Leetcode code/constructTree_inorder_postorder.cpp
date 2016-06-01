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
    TreeNode * buildTree(std::vector<int> & inorder, std::vector<int> & postorder) {
      if (inorder.empty()) return NULL;
      int root_idx = postorder.size() - 1;
      return buildTree(inorder, postorder, 0, root_idx, root_idx);
    }
  private:
    TreeNode * buildTree(std::vector<int> & inorder, std::vector<int> & postorder,
                         int l, int r, int & root_idx) {
      int root_value = postorder[root_idx];
      int i = r;
      for (; i>=0; --i)
        if (inorder[i] == root_value)
          break;
      TreeNode * root = new TreeNode(root_value);
      if (r >= i+1) root->right = buildTree(inorder, postorder, i+1, r, --root_idx);
      if (i-1 >= l) root->left = buildTree(inorder, postorder, l, i-1, --root_idx);
      return root;
    }
};