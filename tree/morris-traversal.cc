#include "utils.h"
#include "internal-util.h"

std::vector<int> MorrisTraverse(TreeNode* root)
{
    std::vector<int> res;
    TreeNode* cur = root, *prev;
    while (cur) {
        if (cur->left == nullptr) {
            res.push_back(cur->data);
            cur = cur->right;
        } else {
            // get the right-most node if left subtree of cur node
            // 根据当前prev前驱节点找到之前连接的cur节点
            // 因为之前cur->left其实并没有断开，一个环又兜回来了
            // 这是下面的while-loop最终会发现prev->right=cur
            // 然后就会断开，处理当前节点cur，之后进入它的右边子树
            prev = cur->left;
            while (prev->right != nullptr && prev->right != cur) {
                prev = prev->right;
            }
            if (prev->right == nullptr) {
                prev->right = cur;  // 连接当前节点与它的前驱节点
                cur = cur->left;
            } else {
                prev->right = nullptr;  // 断开之前连接的cur节点
                res.push_back(cur->data);
                cur = cur->right;
            }
        }
    }
    return res;
}

int main()
{
    TreeNode* root = BuildTree("[1,2,3,4,5,6,7]");
    std::cout << MorrisTraverse(root) << "\n";  // 4,2,5,1,6,3,7
}
