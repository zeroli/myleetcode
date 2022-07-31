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
 /  \      \
7    2      1
*/

// 下面的方法是采用DFS，递归的策略
// 也可以采用BFS，层序遍历的方式
using Path_t = std::vector<int>;
bool PathSum(TreeNode* root, int sum, Path_t& path)
{
    if (!root) return false;
    if (root->left == nullptr && root->right == nullptr) {
        if (sum == root->data) {
            path.push_back(root->data);
            return true;
        }
        return false;
    }
    path.push_back(root->data);
    bool ret = PathSum(root->left, sum - root->data, path) ||
        PathSum(root->right, sum - root->data, path);
    if (ret) {
        return true;
    }
    path.pop_back();
    return false;
}

Path_t PathSum(TreeNode* root, int sum)
{
    Path_t path;
    PathSum(root, sum, path);
    return path;
}

int main()
{
    TreeNode* root = BuildTree("[5,4,8,11,null,13,4,7,2,null,null,null,null,null,1]");
    std::cout << PathSum(root, 22) << "\n";
}
