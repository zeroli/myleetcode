/*
判断二叉树是否高度上平衡，左右子树高度之差不超过1，就是平衡的
*/

/*
遍历每个节点，计算它左右子树的高度，但是计算子树高度时，需要遍历子节点。
在遍历子节点时，又得重复计算下面子树高度。
因此以top到down的方式来判断会有重复运算，因此需要特别的方式。
在计算子树高度时，顺便把子节点的平衡性也计算了。
因此这个过程可以看成时从下到上的方式。
左右子节点返回高度的同时也把是否平衡性算出来。
终究来说，top down的方式就是前序遍历，down up的方式就是后序遍历。
*/

#include "utils.h"
#include "tree/internal-util.h"

bool Traverse(TreeNode* root, int& height)
{
    if (!root) return true;

    int leftHeight = 0, rightHeight = 0;
    bool leftIsBalanced = Traverse(root->left, leftHeight);
    if (!leftIsBalanced) {
        return false;
    }
    bool rightIsBalanced = Traverse(root->right, rightHeight);
    if (!rightIsBalanced) {
        return false;
    }
    // 后序遍历的代码
    height = std::max(leftHeight, rightHeight) + 1;
    // 计算高度的同时也判断当前节点是否平衡
    return ((leftHeight - rightHeight <= 1) && (rightHeight - leftHeight <= 1));
}

bool TreeHeightBalanced(TreeNode* root)
{
    if (!root) return true;
    int height = 0;
    return Traverse(root, height);
}

int main()
{
    {
        TreeNode* root = BuildTree("1, 2, 3, 4, 5");
        std::cout << TreeHeightBalanced(root) << "\n";  // 1
    }
    {
        TreeNode* root = BuildTree("1, 2, 3, 4, null, null, null, 5");
        std::cout << TreeHeightBalanced(root) << "\n";  // 0
    }
}
