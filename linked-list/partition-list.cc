#include "utils.h"
#include "linked-list/internal-util.h"

// 类似于快速排序的partition算法，将链表进行partition
// 左边是小于x的节点，右边是大于等于x的节点
// 但是对于链表，解法比较简单，因为可以将节点单独拿出来
Node* PartitionList(Node* head, int pivot)
{
    // 解法的关键在于建立虚拟节点
    Node smaller;
    Node** ps = &smaller.next;
    Node largerEqual;
    Node** ple = &largerEqual.next;
    while (head) {
        if (head->data < pivot) {
            *ps = head;
            ps = &(head->next);
        } else {
            *ple = head;
            ple = &(head->next);
        }
        head = head->next;
    }
    *ps = largerEqual.next;
    *ple = nullptr;
    return smaller.next;
}

int main()
{
    Node* head = BuildList("1 -> 4 -> 3 -> 2 -> 5 -> 2");
    std::cout << PartitionList(head, 3) << "\n";  // 1 -> 2 -> 2 -> 4 -> 3 -> 5
    DestroyList(head);
}
