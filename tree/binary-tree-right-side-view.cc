#include "utils.h"
#include "tree/internal-util.h"

/*
给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例:

输入: [1,2,3,null,5,null,4]
输出: [1, 3, 4]
解释:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
*/

// 采用层序遍历的方式，每层最后的节点就是right side view
// 但是如何获取每次最后一个元素呢？
// 如果处理每层节点时时从右到左遍历，那么第一个节点就是最右边的节点
// 但是如何从右到左遍历呢？添加节点时先right节点，后left节点，放入到队列中
// 当然也可以借用栈来实现，这样的话，添加节点的顺序仍然是先左后右，
// 弹出的顺序是先右后左，第一个节点就是右边节点
std::vector<int> RightSideView(TreeNode* root)
{
    std::vector<int> res;
    std::queue<TreeNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        int sz = queue.size();
        TreeNode* first = nullptr;
        for (int i = 0; i < sz; i++) {
            TreeNode* cur = queue.front();
            queue.pop();
            if (!first) {
                first = cur;
                res.push_back(cur->data);
            }
            if (cur->right) {
                queue.push(cur->right);
            }
            if (cur->left) {
                queue.push(cur->left);
            }
        }
    }
    return res;
}

int main()
{
    {
        TreeNode* root = BuildTree("1,2,3,null,5,null,4");
        std::cout << RightSideView(root) << "\n";  // 1, 3, 4
    }
    {
        TreeNode* root = BuildTree("1,2,3,null,5,4");
        std::cout << RightSideView(root) << "\n";  // 1, 3, 4
    }
}
