#include "utils.h"
#include "tree/internal-util.h"

/*
    5
   / \
  1   4
     / \
    3   6

Output:
 false

Explanation:
 The input is: [5,1,4,null,null,3,6]. The root node's value
             is 5 but its right child's value is 4.
*/

// 中序遍历，得到有序序列，记录前驱节点，
// 遍历过程中，判断当前节点是否大于前驱节点
// 否则就不是BST树
TreeNode* prev = nullptr;
bool IsBST(TreeNode* root)
{
    if (!root) return true;  // 空节点是BST
    bool leftIsBST = IsBST(root->left);
    if (prev) {
        if (prev->data > root->data) {
            return false;
        }
    }
    prev = root;
    bool rightIsBST = IsBST(root->right);
    return leftIsBST && rightIsBST;
}

// 另外一种方法就是递归判断每棵子树是否满足BST，
// 传入[min, max]进行判断
bool IsBST(TreeNode* root, int min, int max)
{
    if (!root) return true;  // 空节点是BST
    // 前序遍历的位置
    // 判断当前节点是否满足
    if (min > root->data || root->data > max) {
        return false;
    }
    return IsBST(root->left, min, root->data) &&
        IsBST(root->right, root->data, max);
}

int main()
{
    {
        TreeNode* root = BuildTree("[2,1,3]");
        std::cout << std::boolalpha << IsBST(root) << "\n";  // true
    }
    {
        TreeNode* root = BuildTree("[5,1,4,null,null,3,6]");
        std::cout << std::boolalpha << IsBST(root) << "\n";  // false
    }
    {
        TreeNode* root = BuildTree("[2,1,3]");
        std::cout << std::boolalpha << IsBST(root, INT_MIN, INT_MAX) << "\n";  // true
    }
    {
        TreeNode* root = BuildTree("[5,1,4,null,null,3,6]");
        std::cout << std::boolalpha << IsBST(root, INT_MIN, INT_MAX) << "\n";  // false
    }
}
