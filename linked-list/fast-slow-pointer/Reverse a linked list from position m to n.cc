#include "utils.h"
#include "linked-list/internal-util.h"

// It is guaranteed that 1 ≤ m ≤ n ≤ length of linked list
Node* ReverseList(Node* list, int m, int n)
{
    Node* pprev = nullptr;
    Node* beg = list;

    int i = 1;
    // 走m-1步，到达需要反转的头节点
    while (i < m) {
        i++;
        pprev = beg;
        beg = beg->next;
    }
    Node* end = beg;
    // 再走n-m-1步，到达需要反转链表的尾节点
    while (i < n) {
        i++;
        end = end->next;
    }
    end = end->next;
    // reverse区间为[beg, end)
    Node* rlist = ReverseList(beg, end);

    // connect with first part
    if (pprev) {
        pprev->next = rlist;
        rlist = list;
    }
    // connect with 3rd part
    beg->next = end;

    return rlist;
}

int main()
{
    {
        Node* list = BuildList("2->4->6->8->10");
        int m = 2, n = 4;
        std::cout << "input list " << list << "\n";

        list = ReverseList(list, m, n);
        std::cout << "reversed list from " << m << " to " << n << ": " << list << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("2->3->7->9->23");
        int m = 1, n = 5;
        std::cout << "input list " << list << "\n";

        list = ReverseList(list, m, n);
        std::cout << "reversed list from " << m << " to " << n << ": " << list << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("10->20->2->5->9->8");
        int m = 1, n = 5;
        std::cout << "input list " << list << "\n";

        list = ReverseList(list, m, n);
        std::cout << "reversed list from " << m << " to " << n << ": " << list << "\n";
        DestroyList(list);
    }

}
