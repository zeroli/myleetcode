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
// if both p and q located in the tree rooted at root, return LCA
// otherwise if only one found, return that location, else return null
// if root = p/q, then root = lca  (then recurvely call this function may have problem)
//  if root->right/left find how p and q distributed

// if only one found, return that one, if no one found return null, ,if both found return lca
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return root;
        if (root == p || root == q) return root; // check whether exist one
        
        TreeNode* pleft = lowestCommonAncestor(root->left, p , q);
        TreeNode* pright = lowestCommonAncestor(root->right, p , q);
        
        if (pleft && pright) return root; // root is the lca
        if (!pleft && pright) return pright; // right side have one of p and q, need to go up to check where is the other one
        if (pleft && !pright) return pleft;
        if (!pleft && !pright) return NULL;
    }
};