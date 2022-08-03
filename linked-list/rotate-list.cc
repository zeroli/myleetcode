#include "utils.h"
#include "linked-list/internal-util.h"

/*
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。

示例 1:

输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL
示例 2:

输入: 0->1->2->NULL, k = 4
输出: 2->0->1->NULL
解释:
向右旋转 1 步: 2->0->1->NULL
向右旋转 2 步: 1->2->0->NULL
向右旋转 3 步: 0->1->2->NULL
向右旋转 4 步: 2->0->1->NULL
*/

int ListLength(Node* head)
{
    int n = 0;
    while (head) {
        n++;
        head = head->next;
    }
    return n;
}

Node* RotateList(Node* head, int k)
{
    // k有可能大于链表的长度
    // 首先遍历求出整个链表的长度n
    // k = k % n
    // 旋转k次，其实就是将后面k的节点作为整体连接到链表的前面
    int n = ListLength(head);
    k = k % n;
    if (k == 0) return head;

#if 1
    // 利用快慢指针来遍历
    Node* fast = head;
    // k >= 1
    while (k--) {
        fast = fast->next;
    }
    Node* slow = head;
    // 注意这里是判断fast的下一个节点是否为空
    // 也就是fast只遍历到最后一个节点便结束了
    // 这样的话，slow就会到目标节点的前一个节点
    // 题目类似于删除倒数第k个节点的解法
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    fast->next = head;
    head = slow->next;
    slow->next = nullptr;
    return head;
#else
    int steps = n - k - 1;
    Node* prev = head;
    while (steps--) {
        prev = prev->next;
    }
    Node* newhead = prev->next;
    Node* last = newhead;
    steps = k - 1;
    while (steps--) {
        last = last->next;
    }
    assert(last && last->next == nullptr);
    last->next = head;
    prev->next = nullptr;
    return newhead;
#endif
}

int main()
{
    {
        Node* head = BuildList("1,2,3,4,5");
        std::cout << "input list: " << head << "\n";
        std::cout << RotateList(head, 2) << "\n";
    }
    {
        Node* head = BuildList("1,2,3,4,5");
        std::cout << "input list: " << head << "\n";
        std::cout << RotateList(head, 10) << "\n";
    }
    {
        Node* head = BuildList("1,2,3,4,5");
        std::cout << "input list: " << head << "\n";
        std::cout << RotateList(head, 3) << "\n";
    }
    {
        Node* head = BuildList("1,2,3,4,5");
        std::cout << "input list: " << head << "\n";
        std::cout << RotateList(head, 11) << "\n";
    }
    {
        Node* head = BuildList("1");
        std::cout << "input list: " << head << "\n";
        std::cout << RotateList(head, 11) << "\n";
    }
}
