#include "utils.h"
#include "linked-list/internal-util.h"

// 合并排序两个单链表
// 合并区间[list1, nullptr), [list2, nullptr)
Node* Merge(Node* list1, Node* list2)
{
    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";

    Node dummy;
    Node** next = &dummy.next;
    while (list1|| list2) {
        if (list1 == nullptr) {
            *next = list2;
            break;
        } else if (list2 == nullptr) {
            *next = list1;
            break;
        } else if (list1->data < list2->data) {
            *next = list1;
            next = &list1->next;
            list1 = list1->next;
        } else {
            *next = list2;
            next = &list2->next;
            list2 = list2->next;
        }
    }

    std::cout << "merged: " << dummy.next << "\n";
    return dummy.next;
}

// 合并区间[list, nullptr)
Node* MergeSort(Node* list)
{
    if (list && list->next == nullptr) {
        return list;
    }
    Node* mid = FindMiddle2(list);
    Node* list1 = list;
    Node* list2 = mid->next;
    mid->next = nullptr;
    list1 = MergeSort(list1);
    list2 = MergeSort(list2);
    return Merge(list1, list2);
}

int main()
{
    Node* list = BuildList("1, 4, 5, 3, 9, 10, 8, 20, 1, 3, 2, 45, 14");
    std::cout << MergeSort(list) << "\n";
    // 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 8 -> 9 -> 10 -> 14 -> 20 -> 45
}
