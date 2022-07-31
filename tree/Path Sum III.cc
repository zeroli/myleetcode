#include "utils.h"
#include "tree/internal-util.h"

/*
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value

The path does not need to start or end at the root or a leaf,
but it must go downwards (traveling only from parent nodes to child nodes).

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
*/

// 下面的方法是采用DFS，递归的策略
// 也可以采用BFS，层序遍历的方式
using Path_t = std::vector<int>;
void PathSum(TreeNode* root, int targetSum, Path_t& path, std::vector<Path_t>& result)
{
    if (!root) return;

    path.push_back(root->data);
    // 收集路径
    int tmpSum = 0;
    // 从后往前收集，以当前root节点为结尾所有的路径
    for (int i = path.size() - 1; i >= 0; i--) {
        tmpSum += path[i];
        if (tmpSum == targetSum) {
            Path_t tmpPath;
            std::copy(path.begin() + i, path.end(), std::back_inserter(tmpPath));
            result.push_back(tmpPath);
        }
    }

    PathSum(root->left, targetSum, path, result);
    PathSum(root->right, targetSum, path, result);
    path.pop_back();
}

std::vector<Path_t> PathSum(TreeNode* root, int sum)
{
    Path_t path;
    std::vector<Path_t> result;
    PathSum(root, sum, path, result);
    return result;
}

int main()
{
    TreeNode* root = BuildTree("[10,5,-3,3,2,null,11,3,-2,null,1]");
    std::cout << root << "\n";
    std::cout << PathSum(root, 8) << "\n";
}
