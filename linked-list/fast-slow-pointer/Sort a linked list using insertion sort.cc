#include "utils.h"
#include "internal-util.h"

/*
You are given a singly linked list, write a program to sort it using insertion sort.

Problem Note:

    Return the head of the sorted linked list
    Try to solve the problem using in-place algorithm(O(1) space).
*/

Node* InsertInOrder(Node* head, Node* node)
{
    if (head == nullptr) return node;
    if (head == node) return head;

    Node dummy;
    dummy.next = head;

    Node** pp = &dummy.next;
    while (head && head->data < node->data)
    {
        pp = &head->next;
        head = head->next;
    }
    node->next = *pp;
    *pp = node;
    return dummy.next;
}

Node* InsertionSortList(Node* list)
{
    Node* newlist = nullptr;
    Node* node = list;
    while (node) {
        // detach the node
        Node* next = node->next;
        node->next = nullptr;
        newlist = InsertInOrder(newlist, node);
        node = next;
    }
    return newlist;
}

int main()
{
    {
        Node* list = BuildList("4->3->1");
        std::cout << "before sort: " << list << "\n";
        list = InsertionSortList(list);
        std::cout << "after sort: " << list << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("10->4->3->2->1");
        std::cout << "before sort: " << list << "\n";
        list = InsertionSortList(list);
        std::cout << "after sort: " << list << "\n";
        DestroyList(list);
    }
    {
        Node* list = BuildList("1->2->3");
        std::cout << "before sort: " << list << "\n";
        list = InsertionSortList(list);
        std::cout << "after sort: " << list << "\n";
        DestroyList(list);
    }
}
