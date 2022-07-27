#include "utils.h"
#include "internal-util.h"

int FindLongestPath(TreeNode* root, int& diameter)
{
    if (!root) return 0;
    int left = FindLongestPath(root->left, diameter);
    int right = FindLongestPath(root->right, diameter);
    int len = 1;  // we're calculting the path length, not node#
    if (left > 0) {
        len += left;  // add longest path on left
    }
    if (right > 0) {
        len += right;   // add longest path on right
    }
    diameter = std::max(diameter, len);
    int longer = std::max(left, right);
    return longer > 0 ? longer + 1 : 1;
}

int FindDiameter(TreeNode* root)
{
    if (!root) return 0;
    int diameter = 0;
    FindLongestPath(root, diameter);
    // we're counting the node#, so subtract one to get path (edge#)
    return diameter - 1;
}

int main()
{
    {
        TreeNode* root = BuildTree("[2,4,5,6,7]");
        std::cout << "input tree structure:\n" << root << "\n";
        std::cout << FindDiameter(root) << "\n";  // 3
    }
}
