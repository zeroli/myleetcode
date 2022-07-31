#include "utils.h"
#include "tree/internal-util.h"

/*
Given a binary tree and a sum,
 determine if the tree has a root-to-leaf path such that
  adding up all the values along the path equals the given sum.

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1

[
   [5,4,11,2],
   [5,8,4,5]
]
*/

// 下面的方法是采用DFS，递归的策略
// 也可以采用BFS，层序遍历的方式
using Path_t = std::vector<int>;
void PathSum(TreeNode* root, int sum, Path_t& path, std::vector<Path_t>& result)
{
    if (!root) return;
    if (root->left == nullptr && root->right == nullptr) {
        if (sum == root->data) {
            path.push_back(root->data);
            result.push_back(path);
            path.pop_back();
        }
        return;
    }
    path.push_back(root->data);
    PathSum(root->left, sum - root->data, path, result);
    PathSum(root->right, sum - root->data, path, result);
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
    TreeNode* root = BuildTree("[5,4,8,11,null,13,4,7,2,null,null,5,1]");
    std::cout << root << "\n";
    std::cout << PathSum(root, 22) << "\n";
}
