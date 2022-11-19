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

        // p,q could be on two sides of the lca, or one of p or q be lca
        // p, q exist in the tree, repeat left / right until found the node
        
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root->val == p->val || root->val == q->val) return root;
        
        TreeNode* plarger;
        TreeNode* psmaller;
        if (p->val > q->val) {
            plarger = p; psmaller = q;
        } else {
            plarger = q; psmaller = p;
        }
        
        TreeNode* cur = root;
        bool found = false;
        while (!found) {
            if (cur->val >= psmaller->val && cur->val <= plarger->val) found = true;
            while (cur->val > plarger->val)  { cur = cur->left; }
            while (cur->val < psmaller->val)  { cur = cur->right; }
        }
        return cur;
    }
};