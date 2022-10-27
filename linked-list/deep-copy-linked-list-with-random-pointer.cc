/*
A linked list is given such that each node contains an additional random pointer which could point to
any node in the list or null.
Return a deep copy of the list
*/

/*
这题的思路是这样的：
不采用hash table来存储原节点与新节点的对应关系，
而是借用原节点的random指针来指向新节点，
但是新节点的random指针仍然指向源节点的random指针指向的节点
1 -> 2 -> 3 -> 4
  \---------/      /
        \---------/
节点1的random指针3，节点2的random指向4
遍历原链表clone每个节点时，将原节点的random指针指向新节点
1 -> 2 -> 3 -> 4
  \---------/      /
        \---------/
        /--------/
  /--------/
1' -> 2' -> 3' -> 4'
1'的random仍然指向3，2'的random仍然指向4
*/

#include "utils.h"

struct Node {
    Node* random = nullptr;
    Node* next = nullptr;
    int data = 0;
    explicit Node(int d) : data(d) { }
    Node() = default;
};

Node* DeepCopy(Node* head)
{
    if (head == nullptr) return nullptr;

    Node dummy;
    Node* prev = &dummy;
    Node* node = head;
    while (node) {
        Node* newnode = new Node(node->data);
        prev->next = newnode;
        newnode->random = node->random;
        // 借用random节点来位置新旧节点之间的对应关系
        node->random = newnode;
        prev = newnode;
        node = node->next;
    }
    prev->next = nullptr;
    node = head;
    // 再次遍历旧链表，做两件事情：
    // 1. 恢复老节点的random指针指向
    // 2. 让新节点的random指向对应的新节点
    while (node) {
        Node* newnode = node->random;
        node->random = newnode->random;
        // 这个是老节点指向的random节点，它的random就是对应的新random节点
        if (newnode->random) {
            newnode->random = newnode->random->random;
        }
        node = node->next;
    }
    return dummy.next;
}

void Print(Node* node)
{
    fprintf(stderr, "print node list\n");
    if (node == nullptr) return;
    while (node) {
        fprintf(stderr, "node: %d, random points to %p(%d)\n",
           node->data, node->random, (node->random ? node->random->data : -1));
        node = node->next;
    }
}

int main()
{
    {
        Node* node1 = new Node;
        node1->data = 1;
        Node* node2 = new Node;
        node2->data = 2;
        Node* node3 = new Node;
        node3->data = 3;
        Node* node4 = new Node;
        node4->data = 4;
        node1->next = node2;
        node2->next = node3;
        node3->next = node4;
        node4->next = nullptr;
        node1->random = node3;
        node2->random = node4;
        node3->random = nullptr;
        node4->random = nullptr;
        Print(node1);
        Node* node11 = DeepCopy(node1);
        Print(node11);
    }
}
