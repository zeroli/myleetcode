#include "utils.h"
#include "linked-list/internal-util.h"

// 插入排序应用在单链表上
Node* InsertNodeSorted(Node* head, Node* node)
{
    // 共有三种情况需要考虑
    // 1）第一个节点比node要大，node需要插入在链表头
    // 2）中间一个节点比node要大，node插入在那里
    // 3）最后一个节点比node要小，node插入在链表尾
    // 如果要统一处理，可以考虑merge排序的策略，共有2个排好序的链表
    // 其中一个链表只有一个节点
    Node dummy;
    Node** pp = &dummy.next;
    while (node || head) {
        if (node == nullptr) {
            *pp = head;
            break;  // ***** 直接退出，单链表剩下的节点全部链接到返回链表中
        } else if (head == nullptr) {
            *pp = node;
            node->next = nullptr;
            break;  // ***** 直接退出，这个节点链到单链表末尾
        } else if (node->data < head->data) {
            *pp = node;
            pp = &node->next;
            node = node->next;
        } else {
            *pp = head;
            pp = &head->next;
            head = head->next;
        }
    }
    return dummy.next;
}

Node* InsertionSostList(Node* head)
{
    if (!head) return nullptr;

    Node* cur = head->next;
    head->next = nullptr;
    while (cur) {
        // 找到当前节点在排好序的链表上的插入位置
        Node* next = cur->next;
        cur->next = nullptr;
        head = InsertNodeSorted(head, cur);
        cur = next;
    }
    return head;
}

int main()
{
    {
        Node* head = BuildList("4->2->1->3");
        std::cout << InsertionSostList(head) << "\n";  // 1->2->3->4
    }
    {
        Node* head = BuildList("4->3->2->1");
        std::cout << InsertionSostList(head) << "\n";  // 1->2->3->4
    }
    {
        Node* head = BuildList("1->2->3->4");
        std::cout << InsertionSostList(head) << "\n";  // 1->2->3->4
    }
}
