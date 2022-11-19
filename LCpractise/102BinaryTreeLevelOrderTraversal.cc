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
// use to vectors to go through the nodes on the same level
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > lov;
        if (root == NULL) return lov;
        
        vector<TreeNode*> cur(1, root);
        vector<TreeNode*> next;
        
        while (!cur.empty()){
            next.clear();
            lov.push_back(vector<int>());
            for (auto it = cur.cbegin(); it != cur.cend(); ++it){
                lov.back().push_back((*it)->val);
                if ((*it)->left) next.push_back((*it)->left);
                if ((*it)->right) next.push_back((*it)->right);
            }
            swap(cur, next);
        }
        return lov;
    }
};