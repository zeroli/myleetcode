#include "utils.h"
#include "tree/internal-util.h"

/*
边界层序遍历
                  40
                /     \
            20         60
          /    \      /   \
       10      30  50   70
         \              \
           5             55
             \
              45
=> 40, 20, 10, 5, 45, 30, 55, 70, 60
观察发现，
1）前一部分是左子树的边界节点，一直往左，没有左，往右（前序遍历）
2）然后是叶子节点
3）右子树遍历右边界节点，一直往右，没有右，往左，不过顺序是反过来的，
    所有需要bottom-up的遍历（后序遍历可以实现bottom-up的效果）
*/

void TraverseLeftEdge(TreeNode* root, std::vector<int>& path)
{
    if (!root) return;
    // 叶子节点这里不要添加到path，后面叶子节点遍历时会添加
    if (root->left == nullptr && root->right == nullptr) {
        return;
    }
    // 前序遍历代码插入点
    path.push_back(root->data);
    if (root->left) {
        TraverseLeftEdge(root->left, path);
    } else {
        TraverseLeftEdge(root->right, path);
    }
}

void TraverseLeafNodes(TreeNode* root, std::vector<int>& path)
{
    if (!root) return;
    if (root->left == nullptr && root->right == nullptr) {
        path.push_back(root->data);
        return;
    }
    TraverseLeafNodes(root->left, path);
    TraverseLeafNodes(root->right, path);
}

// bottom-up的遍历方式，后序遍历
void TraverseRightEdge(TreeNode* root, std::vector<int>& path)
{
    if (!root) return;
    // 叶子节点这里不要添加到path，前面叶子节点遍历时已经添加
    if (root->left == nullptr && root->right == nullptr) {
        return;
    }
    if (root->right) {
        TraverseRightEdge(root->right, path);
    } else {
        TraverseRightEdge(root->left, path);
    }
    // 后序遍历代码插入点
    path.push_back(root->data);
}

std::vector<int> BoundaryLevelTraverse(TreeNode* root)
{
    std::vector<int> path;
    path.push_back(root->data);
    TraverseLeftEdge(root->left, path);
    TraverseLeafNodes(root, path);
    TraverseRightEdge(root->right, path);
    return path;
}


int main()
{
    TreeNode* root = BuildTree("[40, 20, 60, 10, 30, 50, 70, null, 5, null, null, null, 55, null, null, null, 45");
    std::cout << "boundary level traversal: " << BoundaryLevelTraverse(root) << "\n";
    // 40, 20, 10, 5, 45, 30, 55, 70, 60
}
