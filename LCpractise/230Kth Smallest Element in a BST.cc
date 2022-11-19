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
// use the inorder transverse 
// if the tree is modified often??
    int kthSmallest(TreeNode* root, int k) {
        int count = 0;
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
                ++count;
                if (count == k) return cur->val;
                cur = cur->right;
            }
        }
    }
};