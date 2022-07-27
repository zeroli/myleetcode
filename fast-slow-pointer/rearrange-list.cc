#include "utils.h"
#include "internal-util.h"

Node* RearrangeList(Node* head)
{
    Node* middle = FindMiddle(head);
    Node* rightpart = ReverseList(middle);

    Node dummy;
    Node** pnext = &dummy.next;
    Node* left = head, *right = rightpart;
    while (left && right) {
        if (left == right) break;
        *pnext = left;
        pnext = &(left->next);
        left = left->next;

        *pnext = right;
        pnext = &(right->next);
        right = right->next;
    }
    return dummy.next;
}

int main()
{
    {
        Node* head = nullptr;
        head = InsertNode(head, 2);
        head = InsertNode(head, 4);
        head = InsertNode(head, 6);
        head = InsertNode(head, 8);
        head = InsertNode(head, 10);
        std::cout << "before rearrange: " << head;
        head = RearrangeList(head);
        std::cout << "after rearrange: " << head;
        DestroyList(head);
    }
    {
        Node* head = nullptr;
        head = InsertNode(head, 2);
        head = InsertNode(head, 4);
        head = InsertNode(head, 6);
        head = InsertNode(head, 8);
        head = InsertNode(head, 10);
        head = InsertNode(head, 12);
        std::cout << "before rearrange: " << head;
        head = RearrangeList(head);
        std::cout << "after rearrange: " << head;
        DestroyList(head);
    }
}
