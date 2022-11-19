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
// the difficult thing is to find the fill ratio of the last level, so, level transverse are necessary 
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        if (!root->left && !root->right) return 1;
        if (!root->left || !root->right) return 2;
        
        const TreeNode* pcur = root;
        int heigh = 1;
        while (pcur->left) {
            pcur = pcur->left;
            ++heigh;
        }
        int completeheigh = 1;
        pcur = root;
        while (pcur->right) {
            pcur = pcur->right;
            ++completeheigh;
        }
        assert(heigh - completeheigh <=1);
        if (heigh == completeheigh) return pow(2, heigh)-1;
        
        int level = 1;
        vector<TreeNode*> curlevel(1, root);
        vector<TreeNode*> nextlevel;
        while (level < completeheigh) {
            for (unsigned ii = 0; ii < curlevel.size(); ++ii) {
                nextlevel.push_back(curlevel[ii]->left);
                nextlevel.push_back(curlevel[ii]->right);
            }
            swap(curlevel, nextlevel);
            nextlevel.clear();
            ++level;
        }
        nextlevel.clear();
        for (unsigned ii = 0; ii < curlevel.size(); ++ii) {
            if (!curlevel[ii]->left) break;
            nextlevel.push_back(curlevel[ii]->left);
            if (!curlevel[ii]->right) break;
            nextlevel.push_back(curlevel[ii]->right);
        }
        return pow(2, completeheigh)-1 + nextlevel.size();
    }
};