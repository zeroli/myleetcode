#include "utils.h"
#include "internal-util.h"

int Height(TreeNode* root)
{
    int h = 0;
    while (root) {
        root = root->right;
        h++;
    }
    return h;
}

int CountNode(TreeNode* root)
{
    if (!root) return 0;

    int left_height = 0;
    TreeNode* left = root;
    while (left) {
        left = left->left;
        left_height++;
    }
    int right_height = 0;
    TreeNode* right = root;
    while (right) {
        right = right->right;
        right_height++;
    }

    std::cout << left_height << ", " << right_height << "\n";
    if (left_height == right_height) {  // full tree
        return (1 << left_height) - 1;
    }
    return 1 + CountNode(root->left) + CountNode(root->right);
}

int main()
{
    {
        TreeNode* root = BuildTree("[1,2,3,4,5,6,7,8,9,10]");
        std::cout << CountNode(root) << "\n";
    }
}
