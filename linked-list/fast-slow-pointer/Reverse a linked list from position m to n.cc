#include "utils.h"
#include "internal-util.h"

// It is guaranteed that 1 ≤ m ≤ n ≤ length of linked list
Node* ReverseList(Node* list, int m, int n)
{
    Node* pprev = nullptr;
    Node* beg = list;

    int i = 1;
    int m1 = m;
    while (i < m) {
        i++;
        pprev = beg;
        beg = beg->next;
    }
    Node* end = beg;
    while (i < n) {
        i++;
        end = end->next;
    }
    end = end->next;
    Node* rlist = ReverseList(beg, end);

    // connect with first part
    if (pprev) {
        pprev->next = rlist;
        rlist = list;
    }
    // connect with 3rd part
    if (end) {
        beg->next = end;
    }

    return rlist;
}

int main()
{
    {
        Node* list = BuildList("2->4->6->8->10");
        int m = 2, n = 4;
        std::cout << "list built from " << m << " to " << n << ":\n";
        std::cout << list << "\n";

        list = ReverseList(list, m, n);
        std::cout << "reversed list: " << list << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("2->3->7->9->23");
        int m = 1, n = 5;
        std::cout << "list built from " << m << " to " << n << ":\n";
        std::cout << list << "\n";

        list = ReverseList(list, m, n);
        std::cout << "reversed list: " << list << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("10->20->2->5->9->8");
        int m = 1, n = 5;
        std::cout << "list built from " << m << " to " << n << ":\n";
        std::cout << list << "\n";

        list = ReverseList(list, m, n);
        std::cout << "reversed list: " << list << "\n";
        DestroyList(list);
    }

}
