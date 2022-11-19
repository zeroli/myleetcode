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
// the root at the beginning of preorder will act as spliter of inorder
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) return NULL;
        
        return buildTree(&preorder[0], &inorder[0], preorder.size());
    }
    
private:
    TreeNode* buildTree(int preorder[], int inorder[], int n) {
        TreeNode* root = new TreeNode(preorder[0]);
        
        int ii = 0;
        while (inorder[ii] != root->val && ii < n) ++ii;
        
        if (ii > 0) {
            root->left = buildTree(&preorder[1], &inorder[0], ii);
        }
        else {
            root->left = NULL;
        }
        if (ii < n-1) {
            root->right = buildTree(&preorder[ii+1], &inorder[ii+1], n-ii-1);
        }
        else {
            root->right = NULL;
        }
        
        return root;
    }
};