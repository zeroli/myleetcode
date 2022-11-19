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
// go to the leftmost start from the current node, visit cur left, and then move to its parent in the stack or right
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> values;
        if (!root) return values;
        
        stack<TreeNode*> visited;
        TreeNode* cur = root;
        while (cur || !visited.empty()) {
            if (cur) {
                visited.push(cur);
                cur = cur->left;
            }
            else {
                cur = visited.top();
                visited.pop();
                values.push_back(cur->val);
                cur = cur->right; // if cur is left child and no right for it, this new cur=0 will enable parent to be popped and visited from stack, and then loop to right
            }
        }
        return values;
    }
};