#include "utils.h"
#include "tree/internal-util.h"

// 给定2个节点值，求解它们再二叉查找树的最小公共祖先节点
// 另外类似的题目是，求解的是二叉树，不是二叉查找树

/*
                   40
                 /     \
               20      60
             /   \    /   \
           10   30  50  70
         /              \
       5                 55
    LCA(5, 55) = 40
    LCA(5, 30) = 20
    LCA(60, 70) = 60
*/

// 采用前序遍历，递归求解
TreeNode* LCA_(TreeNode* root, int val1, int val2)
{
    if (!root) return nullptr;
    // 两个节点在当前节点左右两棵子树中，返回这个节点为LCA
    if (val1 <= root->data && root->data <= val2) {
        return root;
    }
    if (val1 < root->data && val2 < root->data) {
        return LCA_(root->left, val1, val2);
    } else {
        return LCA_(root->right, val1, val2);
    }
}

int LCA(TreeNode* root, int val1, int val2)
{
    assert(root);
    TreeNode* lca = LCA_(root, val1, val2);
    return lca->data;
}

int LCA1(TreeNode* root, int val1, int val2)
{
    while (root) {
        // 两个节点在当前节点左右两棵子树中，返回这个节点为LCA
        if (val1 <= root->data && root->data <= val2) {
            return root->data;
        }
        if (val1 < root->data && val2 < root->data) {
            root = root->left;  // 在左子树中继续遍历查找
        } else {
            root = root->right;  // 在右子树中继续遍历查找
        }
    }
    return 0;  // 没找到对应节点
}

int main()
{
    TreeNode* root = BuildTree("[40, 20, 60, 10, 30, 50, 70, 5, null,null,null,null,55]");
    std::cout << LCA(root, 5, 55) << "\n";  // 40
    std::cout << LCA(root, 5, 30) << "\n";  // 20
    std::cout << LCA(root, 60, 70) << "\n";  // 60
    std::cout << LCA1(root, 5, 55) << "\n";  // 40
    std::cout << LCA1(root, 5, 30) << "\n";  // 20
    std::cout << LCA1(root, 60, 70) << "\n";  // 60
}
