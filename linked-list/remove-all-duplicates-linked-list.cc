/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers
from the original list.
For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3
*/

#include "utils.h"
#include "linked-list/internal-util.h"

Node* RemoveDuplicates(Node* head)
{
    if (head == nullptr) return nullptr;

    Node dummy(head->data+1);  // different value from head
    Node* prev = &dummy;
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        // 当前节点与下一个节点不等，保留当前节点
        // 或者这是最后一个节点
        if (!next || cur->data != next->data) {
            prev->next = cur;
            prev = cur;
        } else {
            // 相等的话，我们需要去掉接下来的相等的节点
            // 直到碰到不同的节点，或者null
            while (next && cur->data == next->data) {
                delete cur;
                cur = next;
                next = cur->next;
            }
            // 不管cur是到了最后一个节点，还是一段连续相等节点的最后一个节点
            // cur都要被删除
            // 1: cur, cur, ..., cur, next
            // 2: cur, cur, ..., cur, NULL
            delete cur;
        }
        cur = next;
    }
    prev->next = nullptr;
    return dummy.next;
}

int main()
{
    {
        Node* head = BuildList("1->1->1->1");
        std::cout << (head = RemoveDuplicates(head)) << "\n";  // null
        DestroyList(head);
    }
    {
        Node* head = BuildList("1->1->1->2");
        std::cout << (head = RemoveDuplicates(head)) << "\n";  // 2
        DestroyList(head);
    }
    {
        Node* head = BuildList("1->1->2");
        std::cout << (head = RemoveDuplicates(head)) << "\n";  // 2
        DestroyList(head);
    }
    {
        Node* head = BuildList("1->1->2->3->3->3");
        std::cout << (head = RemoveDuplicates(head)) << "\n";  // 2
        DestroyList(head);
    }
    {
        Node* head = BuildList("1->1->2->3->3->3->5");
        std::cout << (head = RemoveDuplicates(head)) << "\n";  // 2, 5
        DestroyList(head);
    }
    {
        Node* head = BuildList("1->1");
        std::cout << (head = RemoveDuplicates(head)) << "\n";  // null
        DestroyList(head);
    }
    {
        Node* head = BuildList("1");
        std::cout << (head = RemoveDuplicates(head)) << "\n"; // 1
        DestroyList(head);
    }
}
