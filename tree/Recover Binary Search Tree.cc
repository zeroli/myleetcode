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

TreeNode* first = nullptr;
TreeNode* middle = nullptr;
TreeNode* last = nullptr;

/*
case 1:
 
          %
    *  %        
    %  *
 %
 >> 相邻两个%节点交换变成了*
 >> 用first/middle来跟踪
case 2:
           %
   *     %
       % 
     %
   %     *  
 %
 >> 非相邻两个%节点变成了*
 >> 出现2个突然下降，一次是* => %, 一次是% => *
 >> 用first/last来跟踪
*/

void TraverseBSTree(TreeNode* root)
{
    if (!root) return;

    TraverseBSTree(root->left);
    // inorder traversing
    if (prev) {
        if (root->data < prev->data) {
            // 出现第一次突然下降？？
	    if (first == nullptr) {
                first = prev;
                middle = root;
            } else {  // 出现第二次突然下降
                last = root;
            }
        }
    }

    prev = root;
    TraverseBSTree(root->right);
}

TreeNode* RecoverBSTree(TreeNode* root)
{
    TraverseBSTree(root);

    if (first && last) {  // case2
        std::swap(first->data, last->data);
    } else if (first && middle) {  // case 1
        std::swap(first->data, middle->data);
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
