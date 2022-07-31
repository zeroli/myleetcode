#include "utils.h"

/*
Populate each next pointer to point to its next right node.
If there is no next right node, the next pointer should be set toNULL.

     1
   /  \
  2    3
 / \    \
4   5    7

     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \    \
4-> 5 -> 7 -> NULL

*/

// 不再是一个perfect tree
// 采用层序遍历的方式，从根节点开始，
// 每层遍历时已经是一个被前面遍历时搭建好的单链表
// 故可以用next指针进行索引遍历
struct TreeLinkedNode {
    TreeLinkedNode* left = nullptr;
    TreeLinkedNode* right = nullptr;
    TreeLinkedNode* next = nullptr;
    int data;

    TreeLinkedNode(int d)
        : data(d)
    { }

    ~TreeLinkedNode() {
        if (left) delete left;
        if (right) delete right;
    }
};

void Populate(TreeLinkedNode* root)
{
    if (!root) return;

    while (root) {  // 一层层的遍历
        TreeLinkedNode* next = nullptr;  // 接下来一层节点的开头节点
        TreeLinkedNode* prev = nullptr;  // 用于连接用的前面节点
        TreeLinkedNode* cur = root;
        while (cur) {  // 当前层遍历
            if (!next) {
                next = cur->left ? cur->left : cur->right;
            }
            if (cur->left) {
                if (prev) {
                    prev->next = cur->left;
                }
                prev = cur->left;  // 注意需要递进prev指针，以便接下来连接下一个节点
            }
            if (cur->right) {
                if (prev) {
                    prev->next = cur->right;
                }
                prev = cur->right;  // 注意需要递进prev指针，以便接下来连接下一个节点
            }
            cur = cur->next;  // 假设当前层已经用next连接好了
        }
        root = next;
    }
}

int main()
{
    TreeLinkedNode* root = new TreeLinkedNode(1);
    root->left = new TreeLinkedNode(2);
    root->right = new TreeLinkedNode(3);
    root->left->left = new TreeLinkedNode(4);
    root->left->right = new TreeLinkedNode(5);
    root->right->left = nullptr;
    root->right->right = new TreeLinkedNode(7);

    Populate(root);

    assert(root->next == nullptr);
    assert(root->left->next == root->right);
    assert(root->left->left->next == root->left->right);
    assert(root->left->right->next == root->right->right);
    assert(root->right->right->next == nullptr);
    delete root;
}
