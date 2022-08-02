#include "utils.h"
#include "tree/internal-util.h"

/*
Given the root node of a binary tree,
write a program to find the lowest common ancestor (LCA) of
 two given nodes in the tree.

 [5, 6, 3, 1, 7, 9, 4, null, null, 2, 0]
 node1 = 6, node2 = 3
Output: 5

Input: root = [5, 6, 3, 1, 7, 9, 4, null, null, 2, 0]
node1 = 6, node2 = 0
Output: 6
*/

TreeNode* CommonAncester_(TreeNode* root, int n1, int n2)
{
    if (root == nullptr) {
        return nullptr;
    }
    if (root->data == n1 || root->data == n2) {
        return root;
    }
    TreeNode* left = CommonAncester_(root->left, n1, n2);
    TreeNode* right = CommonAncester_(root->right, n1, n2);
    if (left && right) {
        return root;
    }
    if (left) {
        return left;
    }
    if (right) {
        return right;
    }
    return nullptr;
}

int CommonAncester(TreeNode* root, int n1, int n2)
{
    TreeNode* common = CommonAncester_(root, n1, n2);
    if (common) return common->data;
    return -1;
}

int main()
{
    {
        TreeNode* root = BuildTree("[5, 6, 3, 1, 7, 9, 4, null, null, 2, 0]");
        std::cout << root << "\n";
        int n1 = 6, n2 = 3;
        std::cout << CommonAncester(root, n1, n2) << "\n";  // 5
    }
    {
        TreeNode* root = BuildTree("[5, 6, 3, 1, 7, 9, 4, null, null, 2, 0]");
        std::cout << root << "\n";
        int n1 = 6, n2 = 0;
        std::cout << CommonAncester(root, n1, n2) << "\n";  // 6
    }
}
