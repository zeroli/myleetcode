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
// backtracking, keep the string of path in, and roll back. do the recursive to expand the path, and push the result when reach leaf
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) return vector<string>();
        string parentpath;
        vector<string> r;
        binaryTreePaths(root, r, parentpath);
        return r;
    }
    
private:
    void binaryTreePaths(TreeNode* root, vector<string>& r, string& parentpath) {
        string s;
        if (!root->left && !root->right) {
            s = to_string(root->val);
            parentpath += s;
            r.push_back(parentpath);
        } else {
            s = to_string(root->val) + "->";
            parentpath += s;
            if(root->left) binaryTreePaths(root->left, r, parentpath);
            if(root->right) binaryTreePaths(root->right, r, parentpath);
        }
        // backtracking: one has to roll back the parent path to the value when pass in
        parentpath.resize(parentpath.size() - s.size());
    }
};