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
// the depth  =  1 + left one /right one, since each node visited once, O(n)
    int minDepth(TreeNode *root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return 1;
        if (root->left == NULL) return 1+minDepth(root->right);
        if (root->right == NULL) return 1+minDepth(root->left);
        return 1 + min(minDepth(root->right), minDepth(root->left));
    }
};