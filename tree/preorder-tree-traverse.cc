#include "utils.h"
#include "internal-util.h"

void PreorderTraverse_(TreeNode* root, std::vector<int>& res)
{
    if (root == nullptr) {
        return;
    }
    res.push_back(root->data);
    PreorderTraverse_(root->left, res);
    PreorderTraverse_(root->right, res);
}

std::vector<int> PreorderTraverse(TreeNode* root)
{
    std::vector<int> res;
    PreorderTraverse_(root, res);
    return res;
}

std::vector<int> PreorderTraverseIterative(TreeNode* root)
{
    std::vector<int> res;
    if (root == nullptr) {
        return res;
    }
    std::stack<TreeNode*> stk;
    stk.push(root);
    while (!stk.empty()) {
        auto cur = stk.top();
        stk.pop();
        res.push_back(cur->data);

        if (cur->right) {
            stk.push(cur->right);
        }
        if (cur->left) {
            stk.push(cur->left);
        }
    }
    return res;
}

std::vector<int> PreorderTraverseIterative2(TreeNode* root)
{
    // 这是一种特别的方法(标记法)来迭代前序遍历树节点
    std::stack<TreeNode*> stk;
    stk.push(root);

    std::vector<int> res;
    while (!stk.empty()) {
        auto cur = stk.top();
        stk.pop();

        if (cur) {
            if (cur->right) {
                stk.push(cur->right);
            }
            if (cur->left) {
                stk.push(cur->left);
            }
            stk.push(cur);
            stk.push(nullptr);  // mark
        } else {  // visited node, now handle it
            cur = stk.top();
            stk.pop();
            res.push_back(cur->data);
        }
    }
    return res;
}

std::vector<int> MorrisPreorder(TreeNode* root)
{
    std::vector<int> res;

    TreeNode* cur = root, *prev = nullptr;
    while (cur) {
        if (cur->left == nullptr) {
            res.push_back(cur->data);
            cur = cur->right;
        } else {
            prev = cur->left;
            // get the right-most node if left subtree of cur node
            // 根据当前prev前驱节点找到之前连接的cur节点
            // 因为之前cur->left其实并没有断开，一个环又兜回来了
            // 这时下面的while-loop最终会发现prev->right=cur
            // 然后就会断开，处理当前节点cur，之后进入它的右边子树
            while (prev->right != nullptr && prev->right != cur)
            {
                prev = prev->right;
            }
            if (prev->right == nullptr) {
                prev->right = cur;  // 建立连接
                res.push_back(cur->data);  // 第一次见到这个节点，马上进行处理
                cur = cur->left;
            } else {
                prev->right = nullptr;  // 断开连接
                cur = cur->right;  // 调用回来了，不能再处理了
            }
        }
    }
    return res;
}

int main()
{
    {
        TreeNode* root = BuildTree("[1,2,3,null,null,4,5,6]");
        std::cout << root<< "\n";
        std::cout << PreorderTraverse(root) << "\n";  // 1, 2, 3, 4, 6, 5
        std::cout << PreorderTraverseIterative(root) << "\n";  // 1, 2, 3, 4, 6, 5
        std::cout << PreorderTraverseIterative2(root) << "\n";  // 1, 2, 3, 4, 6, 5
        std::cout << MorrisPreorder(root) << "\n";  // 1, 2, 3, 4, 6, 5
    }

}
