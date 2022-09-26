#include "utils.h"
#include "internal-util.h"

int FindLongestPath(TreeNode* root, int& diameter)
{
    if (!root) return -1;
    if (root->left == nullptr && root->right == nullptr) {
        return 0;
    }
    int left = FindLongestPath(root->left, diameter);
    int right = FindLongestPath(root->right, diameter);
    int len = 0;
    if (left >= 0) {
        len += 1 + left;  // add longest path on left
    }
    if (right >= 0) {
        len += 1 + right;   // add longest path on right
    }
    diameter = std::max(diameter, len);
    int longer = std::max(left, right);
    // longer=0, 代表子节点是叶子节点
    return longer > 0 ? longer + 1 : 1;
}

int FindDiameter(TreeNode* root)
{
    if (!root) return 0;
    int diameter = 0;
    FindLongestPath(root, diameter);
    return diameter;
}

int main()
{
    {
        TreeNode* root = BuildTree("[2,4,5,6,7]");
        std::cout << "input tree structure:\n" << root << "\n";
        std::cout << FindDiameter(root) << "\n";  // 3
    }
}
