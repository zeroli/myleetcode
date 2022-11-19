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
// use recursive call to pass the sum from root so far to one intermediate root node, and calculate the sum contributed from the paths with that node
// pass the sum from original root to the current node, and find the path sum so far, add to the total sum
    int sumNumbers(TreeNode* root) {
        int sum = 0; 
        int sumfromroot = 0;
        calSum(root, sum, sumfromroot);
        return sum;
    }
    
private:
    void calSum(TreeNode* root, int& sum, int sumfromroot) { // sumfromroot should be pass by value to avoid carry value back
        if (!root) return;
        sumfromroot = sumfromroot * 10 + root->val;
        if (root->left == NULL && root->right == NULL) {
            sum += sumfromroot; // sumfromroot will be the sum from root to leaf now
            return;
        }
        calSum(root->left,  sum, sumfromroot);// sum will carry the so far left branch value
        calSum(root->right, sum, sumfromroot);
    }
};