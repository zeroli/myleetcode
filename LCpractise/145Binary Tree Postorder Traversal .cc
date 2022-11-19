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
// two different approaches: 
// 1. do the preorder (parent, right, left), and then revert
// 2. DFS, but keep a record whether it is jumped from left or it self when visit the right side
// pseudocode:
//     move to left push into stack q
//     when cur = 0, get the top, if top having right, move to the right side, otherwise visit top: keep a record of whether current is on top's right, that will decide whether top will be visited next
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return vector<int>();
        
        vector<int> r;
        stack<TreeNode*> passed; // but unvisited;
        TreeNode* cur = root;
        TreeNode* lastvisited = NULL;
        while(!passed.empty() || cur == root) {
            if (cur) { // go all the way to left
                passed.push(cur);
                cur = cur->left;
            } else {
                TreeNode* top = passed.top();
                if (top->right && lastvisited != top->right) {// jump to right
                    cur = top->right;
                } else { // visit either there is no right or right already visited
                    r.push_back(top->val);
                    passed.pop();
                    lastvisited = top; // update last visited to know whether to jump to right
                    cur = NULL; // to enable to visit next node in passed stack
                }
            }
        }
        return r;
    }
};