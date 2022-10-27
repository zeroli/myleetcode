/*
Given a sorted linked list, delete all duplicates such that each element appear only once.
For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3
*/

#include "utils.h"
#include "linked-list/internal-util.h"

Node* RemoveDuplicates(Node* head)
{
    if (head == nullptr) return nullptr;

    Node* prev = head;
    Node* cur = head->next;
    while (cur) {
        if (cur->data != prev->data) {
            prev->next = cur;
            prev = cur;
            cur = cur->next;
        } else {
            Node* del = cur;
            cur = cur->next;
            delete del;
        }
    }
    prev->next = nullptr;
    return head;
}

int main()
{
    {
        Node* head = BuildList("1->1->2");
        std::cout << (head = RemoveDuplicates(head)) << "\n";
        DestroyList(head);
    }
    {
        Node* head = BuildList("1->1->2->3->3");
        std::cout << (head = RemoveDuplicates(head)) << "\n";  // 1, 2, 3
        DestroyList(head);
    }
    {
        Node* head = BuildList("1");
        std::cout << (head = RemoveDuplicates(head)) << "\n"; // 1
        DestroyList(head);
    }
}
