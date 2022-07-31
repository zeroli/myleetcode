#include "utils.h"
#include "tree/internal-util.h"

/*
Given a binary tree, check whether it is a mirror of itself
 (ie, symmetric around its center).

     1
   / \
  2   2
 / \ / \
3  4 4  3

    1
   / \
  2   2
   \   \
   3    3
 */

bool TreeSymmetric(TreeNode* left, TreeNode* right)
{
    if (!left && !right) return true;
    if (!left || !right) return false;

    if (left->data != right->data) return false;
    return TreeSymmetric(left->left, right->right) &&
        TreeSymmetric(left->right, right->left);
}

bool TreeSymmetric(TreeNode* root)
{
    if (!root) return false;
    return TreeSymmetric(root->left, root->right);
}

int main()
{
    {
        TreeNode* root = BuildTree("[1,2,2,3,4,4,3]");
        std::cout << std::boolalpha << TreeSymmetric(root) << "\n";  // true
    }
    {
        TreeNode* root = BuildTree("[1,2,2,null,3,null,3]");
        std::cout << std::boolalpha << TreeSymmetric(root) << "\n";  // false
    }
}
