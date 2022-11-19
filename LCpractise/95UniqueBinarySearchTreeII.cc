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
// recursively to generate the left possible trees and right possible trees, and merge them togehter with the root (1..n)
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode *>* pret;
        pret = generateTrees(1, n);
        return *pret;
    }
    
private:
    vector<TreeNode*>* generateTrees(int m, int n){
        vector<TreeNode*>* r= new vector<TreeNode*>();
        if (n<m) {r->push_back(NULL); return r;}
        if (n==m) {
            TreeNode* root = new TreeNode(m);
            r->push_back(root);
            return r;
        }
        
        for (int ii = m; ii <= n; ++ii) {
            vector<TreeNode*>* pvleft, *pvright;
            pvleft = generateTrees(m, ii-1); // generate left
            pvright = generateTrees(ii+1, n); // generate right
            
            for (int il = 0; il < pvleft->size(); ++il) // merge
            for (int ir = 0; ir < pvright->size(); ++ir) {
                TreeNode* root = new TreeNode(ii);
                root->left = (*pvleft)[il];
                root->right = (*pvright)[ir];
                r->push_back(root);
            }
        }
        return r;
    }
};