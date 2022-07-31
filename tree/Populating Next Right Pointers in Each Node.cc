#include "utils.h"

/*
Given a binary tree
Populate each next pointer to point to its next right node.
 If there is no next right node, the next pointer should be set toNULL.
You may assume that it is a perfect binary tree
(ie, all leaves are at the same level, and every parent has two children).

     1
   /  \
  2    3
 / \  / \
4  5  6  7

     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \  / \
4->5->6->7 -> NULL
*/

// 注意这是一个perfect tree，所有叶子节点在同一层
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

void Connect(TreeLinkedNode* node, TreeLinkedNode* next)
{
    node->next = next;
}

void Populate(TreeLinkedNode* root, TreeLinkedNode* sibling = nullptr)
{
    if (!root) return;
    Connect(root, sibling);
    Populate(root->left, root->right);
    if (sibling) {
        Populate(root->right, sibling->left);
    } else {
        Populate(root->right, nullptr);
    }
}

int main()
{
    TreeLinkedNode* root = new TreeLinkedNode(1);
    root->left = new TreeLinkedNode(2);
    root->right = new TreeLinkedNode(3);
    root->left->left = new TreeLinkedNode(4);
    root->left->right = new TreeLinkedNode(5);
    root->right->left = new TreeLinkedNode(6);
    root->right->right = new TreeLinkedNode(7);

    Populate(root);

    assert(root->next == nullptr);
    assert(root->left->next == root->right);
    assert(root->left->left->next == root->left->right);
    assert(root->left->right->next == root->right->left);
    assert(root->right->left->next == root->right->right);
    assert(root->right->right->next == nullptr);
    delete root;
}
