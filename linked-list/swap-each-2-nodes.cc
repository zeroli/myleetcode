#include "utils.h"
#include "linked-list/internal-util.h"

// 两两交换链表中的节点
Node* Swap2Nodes(Node* begin)
{
    Node* next = begin->next;
    if (next) {
        Node* last = next->next;
        begin->next = last;
        next->next = begin;
        return next;
    } else {
        return begin;
    }
}

Node* SwapEach2Nodes(Node* head)
{
    if (!head) return nullptr;
    // 注意这里需要更新head，因为swap2nodes已经修改了head的指向
    head = Swap2Nodes(head);
    // 从而下面才能索引到正确的链表节点
    if (head->next && head->next->next) {
        head->next->next = SwapEach2Nodes(head->next->next);
    }
    return head;
}

int main()
{
    {
        Node* list = BuildList("1,2,3,4,5,6");
        std::cout << "input list: " << list << "\n";
        std::cout << SwapEach2Nodes(list) << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("1,2,3,4,5");
        std::cout << "input list: " << list << "\n";
        std::cout << SwapEach2Nodes(list) << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("");
        std::cout << "input list: " << list << "\n";
        std::cout << SwapEach2Nodes(list) << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("1");
        std::cout << "input list: " << list << "\n";
        std::cout << SwapEach2Nodes(list) << "\n";
        DestroyList(list);
    }
}
