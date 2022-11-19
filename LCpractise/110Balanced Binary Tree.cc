/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int Depth(TreeNode* root){
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return 1;
        if (root->left == NULL) return 1+Depth(root->right);
        if (root->right == NULL) return 1+Depth(root->left);
        return 1 + max(Depth(root->right), Depth(root->left));
    }
    bool isBalanced(TreeNode *root) {
        if (root == NULL) return true;
        return (isBalanced(root->left) && isBalanced(root->right) && abs(Depth(root->left) - Depth(root->right)) <= 1);
    }
};