#include "utils.h"
#include "internal-util.h"

void PostorderTraverse_(TreeNode* root, std::vector<int>& res)
{
    if (root == nullptr) return;

    PostorderTraverse_(root->left, res);
    PostorderTraverse_(root->right, res);
    res.push_back(root->data);
}

std::vector<int> PostorderTraverse(TreeNode* root)
{
    std::vector<int> res;
    PostorderTraverse_(root, res);
    return res;
}

std::vector<int> MorrisPostorder(TreeNode* root)
{
    std::vector<int> res;
    TreeNode* cur = root, *next = nullptr;
    // 解法类似于morris的前序遍历，只是left/right遍历时进行交换
    // 先right，然后再left，最后将res进行反转，就是后序遍历的结果
    while (cur) {
        if (cur->right == nullptr) {
            res.push_back(cur->data);
            cur = cur->left;
        } else {
            next = cur->right;
            while (next->left != nullptr && next->left != cur)
            {
                next = next->left;
            }
            if (next->left == nullptr) {
                next->left = cur;
                res.push_back(cur->data);
                cur = cur->right;
            } else {
                next->left = nullptr;
                cur = cur->left;
            }
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::vector<int> PostorderTraverseIterative(TreeNode* root)
{
    // 这是一种特别的方法(标记法)来迭代后序遍历树节点
    std::stack<TreeNode*> stk;
    stk.push(root);

    std::vector<int> res;
    while (!stk.empty()) {
        auto cur = stk.top();
        stk.pop();

        if (cur) {
            stk.push(cur);
            stk.push(nullptr);  // mark

            if (cur->right) {
                stk.push(cur->right);
            }
            if (cur->left) {
                stk.push(cur->left);
            }
        } else {  // visited node, now handle it
            cur = stk.top();
            stk.pop();
            res.push_back(cur->data);
        }
    }
    return res;
}

// 另外一个非递归的方式实现post-order traversal
std::vector<int> PostorderTraverseIterative1(TreeNode* root)
{
    std::vector<int> res;
    std::stack<TreeNode*> stk;
    stk.push(root);
    // 模拟post recursive的方式，采用栈
    TreeNode* prev = nullptr;

    /*
    void traverse(root, prev = nullptr) {
      if (root == null) return;
      traverse(root->left, root);
      traverse(root->right, root);
      print(root->data);
    }
    */
    while (!stk.empty()) {
        TreeNode* cur = stk.top();
        if (prev == nullptr || (prev->left == cur) || (prev->right == cur))
        {
            if (cur->left != nullptr) {  // 一直走左边
                stk.push(cur->left);
            } else if (cur->right != nullptr) {  // 一开始没有左树，走右边
                stk.push(cur->right);
            } else {  // 到达叶子节点
                res.push_back(cur->data);
                stk.pop();  // 栈退回一层
            }
        } else if (cur->left == prev) {  // 从左子树退出
            if (cur->right != nullptr) {  // 右子树存在，走右边
                stk.push(cur->right);
            } else {  // 不存在右子树，当前节点结束遍历
                res.push_back(cur->data);
                stk.pop();  // 栈退回一层
            }
        } else {  // 从右子树退出
            res.push_back(cur->data);
            stk.pop();
        }
        prev = cur;
    }
    return res;
}

int main()
{
    {
        TreeNode* root = BuildTree("[1,2,3,null,null,4,5,6]");
        std::cout << root<< "\n";
        std::cout << PostorderTraverse(root) << "\n";  // 2,6,4,5,3,1
        std::cout << PostorderTraverseIterative(root) << "\n";  // 2,6,4,5,3,1
        std::cout << MorrisPostorder(root) << "\n";  // 2,6,4,5,3,1
        std::cout << PostorderTraverseIterative1(root) << "\n";  // 2,6,4,5,3,1
    }
}
