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
/*
// Better method ****
// use a static point point to the parent in recursively call to make the comparison
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        
        static TreeNode* prv = 0;
        if (!isValidBST(root->left)) return false;
        if (prv && prv->val >= root->val) return false;
        prv = root; // update pre for the right branch
        return isValidBST(root->right); // update pre to be right pre one in the left branch
    }
*/
    /* does not work with val = INT_MIN */
    // do the inorder and check whether it is in order. 
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        
        int cur_MAX = INT_MIN;
        stack<TreeNode*> visited;
        TreeNode* cur = root;
        bool reach_leftmost = false;
        TreeNode* leftmost = root;
        while (cur || !visited.empty()) {
            if (cur) {
                visited.push(cur);
                if (!reach_leftmost) leftmost = cur;
                cur = cur->left;
            }
            else {
                reach_leftmost = true;
                cur = visited.top();
                visited.pop();
                if (cur != leftmost && cur->val <= cur_MAX) return false;
                cur_MAX = cur->val;
                cur = cur->right;
            }
        }
        return true;
    }
    
};