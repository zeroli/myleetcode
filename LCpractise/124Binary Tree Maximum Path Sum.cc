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
// for any path through a node: there are two posiblities: either this node is the top or below top:
// for each node, there are two different kind of paths: paths with it as top; and paths with pass its parent
// the overall sum is the maximum of sums among the first kinds of paths for all node.
// to calculate such sum, one needs the subsum for the second kind of path
// therefore define 
// max_top(a): the max with a as top
// max_pass(a): the max with the path pass through a's parent, this sum is the subsum in the substree rooted at a;

// the following recursive relation: 
//      max_top(a) = max(max_pass(a.left)+max_pass(a.right), max_pass(a.left), max_pass(a.right), 0)+a.val
//      max_pass(a) = max(max_pass(a.left)+a.val, max_pass(a.right)+a.val, a.val)
// the maximum sum of max_top(a) is the result

// one extension is the maxpath from root to leaf: recursive: findMax(a) = (findMax(a.left), find(a.right)) + root.val
// another extension is the maxpath between two leaves: compare result on left and right, + root to left/right
    int maxPathSum(TreeNode* root) {
        if (!root) return 0;
        int r = INT_MIN;
        findSums(root, r);
        return r;
    }
    
    int findSums(TreeNode* root, int& r) {
        if (!root) return 0;
        int max_pass_left = findSums(root->left, r);
        int max_pass_right = findSums(root->right, r);
        int max_top = max(max(max(max_pass_left + max_pass_right, max_pass_left), max_pass_right), 0) + root->val;
        r = max(r, max_top);
        return max(0, max(max_pass_left, max_pass_right)) + root->val;
    }

};