#ifndef SLOW_FASTER_INTERNAL_UTIL_H_
#define SLOW_FASTER_INTERNAL_UTIL_H_

#include <cassert>
#include <string>

struct Node {
    int data = 0;
    Node* next = nullptr;

    Node() = default;
    Node(int d) : data(d) { }
};

// insert new node with 'data' before `head`, return new head
Node* InsertNode(Node* head, int data)
{
    if (head) {
        Node* node = new Node(data);
        node->next = head;
        head = node;
    } else {
        head = new Node(data);
    }
    return head;
}

// recursively
#if 0
Node* ReverseList(Node* head)
{
    if (head && !head->next) {
        return head;
    }
    if (!head) {
        return nullptr;
    }
    Node* newhead = ReverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newhead;
}
#endif

// reverse list in range [beg, end)
Node* ReverseList(Node* beg, Node* end = nullptr)
{
    Node* cur = beg, *prev = nullptr, *next = nullptr;
    while (cur != end) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

Node* FindMiddle(Node* head)
{
    assert(head);
    Node* fast = head, *slow = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

void DestroyList(Node* head)
{
    if (!head) return;
    DestroyList(head->next);
    delete head;
}

void PrintList(Node* head, std::ostream& out)
{
    while (head) {
        out << head->data << " -> ";
        head = head->next;
    }
    out << "null\n";
}

std::ostream& operator <<(std::ostream& outstr, Node* head)
{
    PrintList(head, outstr);
    return outstr;
}

Node* BuildList(const std::string& str)
{
    Node dummy;
    Node** pp = &dummy.next;
    for (int i = 0; i < str.size(); ) {
        if (std::isdigit(str[i])) {
            int val = 0;
            while (i < str.size() && std::isdigit(str[i])) {
                val = 10 * val + str[i] - '0';
                i++;
            }
            *pp = new Node(val);
            pp = &((*pp)->next);
        } else {
            i++;
        }
    }
    return dummy.next;
}

#endif  // SLOW_FASTER_INTERNAL_UTIL_H_
