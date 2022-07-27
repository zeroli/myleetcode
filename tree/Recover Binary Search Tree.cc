#include "utils.h"
#include "internal-util.h"

/*
Given a binary search tree(BST) whose two elements are swapped by mistake.
 Write a program to recover the tree without changing its structure.

Problem Note

    A solution using O(n) space is pretty straight forward.
     Could you think of a better constant space solution?
*/

TreeNode* pprev = nullptr;
TreeNode* prev = nullptr;

TreeNode* wrong1 = nullptr;
TreeNode* wrong2 = nullptr;

// find wrong1/wrong2 when traversing
void TraverseBSTree(TreeNode* root)
{
    if (!root) return;

    TraverseBSTree(root->left);
    // inorder traversing
    if (prev) {
        if (root->data < prev->data) {
            // any sudden smaller, think it as wrong2
            wrong2 = root;
            // wrong1/wrong2 might be near
            if (pprev && pprev->data < prev->data) {
                wrong1 = prev;
            }
        }
    }

    pprev = prev;
    prev = root;
    TraverseBSTree(root->right);
}

TreeNode* RecoverBSTree(TreeNode* root)
{
    TraverseBSTree(root);

    if (wrong1 && wrong2) {
        std::swap(wrong1->data, wrong2->data);
    }

    return root;
}

int main()
{
    {
        TreeNode* root = BuildTree("[10, 5, 8, 2, 20]");
        std::cout << "input wrong BST: \n" << root << "\n";
        std::cout << "fixed BST: \n" << RecoverBSTree(root) << "\n";
    }
    {
        TreeNode* root = BuildTree("[3,1,5,null,null,2]");
        std::cout << "input wrong BST: \n" << root << "\n";
        std::cout << "fixed BST: \n" << RecoverBSTree(root) << "\n";
    }
}
