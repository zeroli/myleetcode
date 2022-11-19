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
// level transvers with two queues, and put the last element int result vector
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return vector<int>();
        
        vector<int> r;
        queue<TreeNode*> qcur, qnext;
        qcur.push(root);
        while (!qcur.empty()) {
            TreeNode* n = qcur.front();
            qcur.pop();
            
            if (n->left) qnext.push(n->left);
            if (n->right) qnext.push(n->right);
            
            if (qcur.empty())  {
                r.push_back(n->val);
                swap(qcur, qnext);
            }
        }
        return r;
    }
};