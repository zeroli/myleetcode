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
// split in the midder
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(&nums[0], nums.size());
    }
    
private:
    TreeNode* sortedArrayToBST(int nums[], int n) {
        if (n == 0) return NULL;
        TreeNode* root = new TreeNode(nums[n/2]); // left has at most one more element
        if (n == 1) return root;
        root->left = sortedArrayToBST(&nums[0], n/2);
        root->right = sortedArrayToBST(&nums[n/2+1], n-n/2-1);
        return root;
    }
};