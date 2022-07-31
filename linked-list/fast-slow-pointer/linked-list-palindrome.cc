#include "utils.h"
#include "internal-util.h"

bool ListIsPalindrome(Node* head)
{
    if (!head) return false;

    Node* fast = head, *slow = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* leftpart = head;
    Node* rightpart = ReverseList(slow);
    Node* tmp = rightpart;
    bool ret = true;
    while (leftpart && rightpart) {
        if (leftpart->data != rightpart->data) {
            ret = false;
            break;
        }
        leftpart = leftpart->next;
        rightpart = rightpart->next;
    }
    ReverseList(tmp);
    return ret;
}

int main()
{
    {
        Node* head = nullptr;
        head = InsertNode(head, 2);
        head = InsertNode(head, 4);
        head = InsertNode(head, 6);
        head = InsertNode(head, 4);
        head = InsertNode(head, 2);
        std::cout << std::boolalpha << ListIsPalindrome(head) << "\n";
        DestroyList(head);
    }
    {
        Node* head = nullptr;
        head = InsertNode(head, 2);
        head = InsertNode(head, 4);
        head = InsertNode(head, 6);
        head = InsertNode(head, 4);
        head = InsertNode(head, 2);
        head = InsertNode(head, 2);
        std::cout << std::boolalpha << ListIsPalindrome(head) << "\n";
        DestroyList(head);
    }
}
