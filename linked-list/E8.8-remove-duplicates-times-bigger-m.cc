/*
给定一个排序的单链表，对于任意一个节点，
如果它重复次数超过m，都要删除掉
*/

#include "utils.h"
#include "linked-list/internal-util.h"

Node* DeleteNodes(Node* prev, int k)
{
    Node* cur = prev->next;
    while (k--) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    prev->next = cur;
    return prev;
}

Node* RemoveDuplicatesGreaterThan(Node* head, int m)
{
    Node dummy;
    dummy.next = head;
    Node* prev = &dummy;
    Node* cur = head;
    int cnt = 0;
    while (cur) {
        cnt++;
        Node* next = cur->next;
        // 到了末尾，或者遇到不同节点，都要判断是否统计超过了m
        if (!next || cur->data != next->data) {
            if (cnt > m) {  // 超过m次了
                prev = DeleteNodes(prev, cnt);
            } else {  // 没超过，我们需要更新prev节点为cur
                prev = cur;  // ***
            }
            cnt = 0;  // 重置个数为0，因此要新一轮的遍历统计了
        }
        cur = next;
    }
    return dummy.next;
}

int main()
{
    {
        Node* head = BuildList("0->1->1->1->2->3");
        std::cout << RemoveDuplicatesGreaterThan(head, 2) << "\n"; // 0->2->3
    }
    {
        Node* head = BuildList("0->1->1->1->2->2->3");
        std::cout << RemoveDuplicatesGreaterThan(head, 2) << "\n"; // 0->2->2->3
    }
    {
        Node* head = BuildList("0->1->1->1->2->2->3");
        std::cout << RemoveDuplicatesGreaterThan(head, 1) << "\n"; // 0->3
    }
    {
        Node* head = BuildList("0->0->1->1->1->2->2->3");
        std::cout << RemoveDuplicatesGreaterThan(head, 1) << "\n"; // 3
    }
    {
        Node* head = BuildList("0->1->2->3->3");
        std::cout << RemoveDuplicatesGreaterThan(head, 1) << "\n"; // 0->1->2
    }
}
