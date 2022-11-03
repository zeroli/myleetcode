/*
反转单链表，从m到n，inclusive，m从1开始
*/

/*
这里提供另一个反转单链表的方式，也是迭代的方式，但是跟我们之前会有所不同
0 -> 1 -> 2 -> 3 -> 4 -> 5, 反转节点1到节点4，包括节点4
开始时，当前节点指向1
第零次:  0 -> 1 -> 2 -> 3 -> 4 -> 5
第一次：0 -> 2 -> 1 -> 3 -> 4 -> 5 (反转1->2，当前节点指向1)
第二次：0 -> 3 -> 2 -> 1 -> 4 -> 5 (将1的下一个节点连接到0后面，1的next指向之前节点3的下一个节点4）
第三次：0 -> 4 -> 3 -> 2 -> 1 -> 5 (将1的下一个节点连接到0后面，1的next指向之前节点4的下一个节点5)
这样下来，随着节点1不断向前进，它遇到的节点一个个的连接到0的后面，从而达到最后链表反转的目的
*/

#include "utils.h"
#include "linked-list/internal-util.h"

Node* ReverseSublist(Node* head, int start, int finish)  // [start, finish]
{
    Node dummy;
    dummy.next = head;
    Node* prev = &dummy;
    int k = 1;
    while (k++ < start) {
        prev = prev->next;
    }
    Node* cur = prev->next;
    // 因此一次遍历就可以反转完对应的区间
    // 不需要先遍历到对应的end，然后再进行反转
    while (start++ < finish) {
        Node* next = cur->next;
        cur->next = next->next;
        next->next = prev->next;
        prev->next = next;  // no change to prev
    }
    return dummy.next;
}

int main()
{
    {
        Node* head = BuildList("0->1->2->3->4->5");
        std::cout << ReverseSublist(head, 2, 5) << "\n";  // 0 -> 4 -> 3 -> 2 -> 1 -> 5 -> null
    }
    {
        Node* head = BuildList("0->1->2->3->4->5");
        std::cout << ReverseSublist(head, 2, 6) << "\n";  // 0 -> 5- > 4 -> 3 -> 2 -> 1 -> null
    }
    {
        Node* head = BuildList("0->1->2->3->4->5");
        std::cout << ReverseSublist(head, 1, 6) << "\n";  // 5- > 4 -> 3 -> 2 -> 1 -> 0 -> null
    }
}
