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
// similar to inorder + preorder
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty()) return NULL;
        
        return buildTree(&inorder[0], &postorder[0], postorder.size());
    }
    
private:
    TreeNode* buildTree(int inorder[], int postorder[], int n) {
        TreeNode* root = new TreeNode(postorder[n-1]);
        
        int ii = 0;
        while (inorder[ii] != root->val && ii < n) ++ii;
        
        if (ii > 0) {
            root->left = buildTree(&inorder[0], &postorder[0], ii);
        }
        else {
            root->left = NULL;
        }
        if (ii < n-1) {
            root->right = buildTree(&inorder[ii+1], &postorder[ii], n-ii-1);
        }
        else {
            root->right = NULL;
        }
        
        return root;
    }
};