#include "utils.h"
#include "tree/internal-util.h"

/*
ou are given the root of a binary tree.
 We install cameras on the tree nodes where each camera
  at a node can monitor its parent, itself, and its immediate children.

Return the minimum number of cameras needed to monitor all nodes of the tree.

Input: root = [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed as shown.

Input: root = [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree.
 The above image shows one of the valid configurations of camera placement.

*/

// 每个节点有3中状态：
enum {
    MONITORED = 1,  // 被子节点照亮了
    UN_MONOTORED = 2,  // 没被子节点照亮
    CAMERA = 3  // 有camera安装
};

// 有几种状态：
/*
    =>>>只要有一个子节点没被照亮，父节点得需要一个camera
       C            C            C
     /  \          / \          / \
    U   U        U  M      U  C
    ===============
      M            M          U
     /  \           / \         / \
    C   C        C  M     M  M
    =>>>只要有一个子节点有camera，父节点就会被monitored
    =>>>子节点都为M，则父节点则是U

  ****叶子节点不能放camera，因为它下面没有子节点，放则不划算
*/
// 返回当前节点对应的状态给父节点
int BinaryTreeCamera_(TreeNode* root, int& total)
{
    if (!root) return 0;  // 返回0，告诉叶子节点un monitored
    int left = BinaryTreeCamera_(root->left, total);
    int right = BinaryTreeCamera_(root->right, total);
    if (left == UN_MONOTORED || right == UN_MONOTORED) {
        // 统计需要camera的个数
        total++;
        return CAMERA;
    }
    if (left == CAMERA || right == CAMERA) {
        return MONITORED;
    }
    // 子节点都是M，当前节点就是un monitored
    return UN_MONOTORED;
}

// 返回整棵树至少需要多少camera
int BinaryTreeCamera(TreeNode* root)
{
    int total = 0;
    int ret = BinaryTreeCamera_(root, total);
    if (ret == UN_MONOTORED)
        total++;
    return total;
}

int main()
{
    {
        TreeNode* root = BuildTree("[0,0,null,0,0]");
        std::cout << "tree: " << root << "\n";
        std::cout << BinaryTreeCamera(root) << "\n";
    }
    {
        TreeNode* root = BuildTree("[0,0,null,0,null,0,null,null,0]");
        std::cout << "tree: " << root << "\n";
        std::cout << BinaryTreeCamera(root) << "\n";
    }
}
