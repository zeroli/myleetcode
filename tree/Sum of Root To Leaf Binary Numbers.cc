#include "utils.h"
#include "tree/internal-util.h"

/*
You are given the root of a binary tree where each node has a value 0 or 1.
 Each root-to-leaf path represents a binary number starting with the most significant bit.

    For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.

For all leaves in the tree, consider the numbers represented by the path from the root to that leaf.
Return the sum of these numbers.

The test cases are generated so that the answer fits in a 32-bits integer.
*/

// 采用DFS，先序遍历的方式，一旦达到叶子节点，
// 将路径累加和加到最终结果和中
void SumRoot2Leaf(TreeNode* root, int pathSum, int& totalSum)
{
    if (!root) return;
    pathSum = (pathSum << 1) | root->data;
    if (root->left == nullptr && root->right == nullptr) {
        totalSum += pathSum;
        return;
    }
    SumRoot2Leaf(root->left, pathSum, totalSum);
    SumRoot2Leaf(root->right, pathSum, totalSum);
}

int SumRoot2Leaf(TreeNode* root, int sum = 0)
{
    int totalSum = 0;
    SumRoot2Leaf(root, 0, totalSum);
    return totalSum;
}

int main()
{
    {
        TreeNode* root = BuildTree("1,0,1,0,1,0,1");
        std::cout << SumRoot2Leaf(root) << "\n";  // 22
    }
    {
        TreeNode* root = BuildTree("0");
        std::cout << SumRoot2Leaf(root) << "\n";  // 0
    }
}
