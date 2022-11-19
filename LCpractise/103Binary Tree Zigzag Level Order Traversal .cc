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
// use two stacks: one for current level, and one for next level
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> r;
        if (!root) return r;
        
        stack<TreeNode*> currlev;
        currlev.push(root);
        stack<TreeNode*> nextlev;
        bool toright = true;
        
        while(!currlev.empty()) {
            vector<int> rlevel;
            while (!currlev.empty()) {
                TreeNode* n = currlev.top();
                rlevel.push_back(n->val);
                currlev.pop();
                TreeNode* first = toright? n->left : n->right;
                TreeNode* second = toright? n->right : n->left;
                if (first) nextlev.push(first);
                if (second) nextlev.push(second);
            }
            r.push_back(rlevel);
            swap(currlev, nextlev);
            toright = !toright;
        }
        return r;
    }
};