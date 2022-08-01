#include "utils.h"
#include "linked-list/internal-util.h"

Node* ZipList(Node* list)
{
    if (!list) return list;

    Node* middle = FindMiddle(list);
    Node* list2 = middle->next;
    middle->next = nullptr;
    list2 = ReverseList(list2);
    Node dummy;
    Node** pnext = &dummy.next;
    while (list || list2) {
        if (list) {
            *pnext = list;
            pnext = &list->next;
            list = list->next;
        }
        if (list2) {
            *pnext = list2;
            pnext = &list2->next;
            list2 = list2->next;
        }
    }
    return dummy.next;
}

int main()
{
    {
        Node* list = BuildList("1,2,3,4");
        std::cout << "original list: " << list << "\n";
        std::cout << ZipList(list) << "\n";  // 1, 4, 2, 3
        DestroyList(list);
    }
    {
        Node* list = BuildList("1,2,3,4,5");
        std::cout << "original list: " <<  list << "\n";
        std::cout << ZipList(list) << "\n";  // 1, 5, 2, 4, 3
        DestroyList(list);
    }
    {
        Node* list = BuildList("1");
        std::cout << "original list: " <<  list << "\n";
        std::cout << ZipList(list) << "\n";  // 1
        DestroyList(list);
    }
    {
        Node* list = BuildList("1, 2");
        std::cout << "original list: " <<  list << "\n";
        std::cout << ZipList(list) << "\n";  // 1, 2
        DestroyList(list);
    }
}
