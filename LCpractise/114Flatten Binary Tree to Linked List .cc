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
// store the right child into a stack (therefore keep the right branch), and move the left child to right side (keep the left branch), if there is no left/right branch, i.e. leaf, get the top from stack as its right child, ..., keep recursively
    void flatten(TreeNode* root) {
        if (!root) return;
        
        stack<TreeNode*> rights;
        TreeNode* pcur = root;
        
        while (pcur || !rights.empty()) {
            
            if (pcur->left) {
                if (pcur->right) rights.push(pcur->right);
                pcur->right = pcur->left;
                pcur->left = NULL;
            }
            else if (!pcur->right && !rights.empty()) {
                pcur->right = rights.top();
                rights.pop();
            }
            pcur = pcur->right;

        }
    }
    
};