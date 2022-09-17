#ifndef LINKED_LIST_INTERNAL_UTIL_H_
#define LINKED_LIST_INTERNAL_UTIL_H_

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

Node* FindMiddle(Node* head, Node* end = nullptr)
{
    assert(head);
    Node* fast = head, *slow = head;
    // 对于奇数区间[head, end), slow将会是中间的那一个
    // 对于偶数区间[head, end), slow将会是n/2 + 1的那一个
    while (fast != end && fast->next != end) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

Node* FindMiddle2(Node* head, Node* end = nullptr)
{
    assert(head);
    Node* fast = head, *slow = head;
    // 对于奇数区间[head, end), slow将会是中间的那一个
    // 对于偶数区间[head, end), slow将会是n/2的那一个
    while (fast != end && fast->next != end) {
        fast = fast->next->next;
        if (fast != end) {
            slow = slow->next;
        }
    }
    return slow;
}

void DestroyList(Node* head)
{
    if (!head) return;
    DestroyList(head->next);
    delete head;
}

void PrintList(std::ostream& out, Node* head, Node* end = nullptr)
{
    while (head && head != end) {
        out << head->data << " -> ";
        head = head->next;
    }
    out << "null";
}

std::ostream& operator <<(std::ostream& outstr, Node* head)
{
    PrintList(outstr, head, nullptr);
    return outstr;
}

Node* BuildList(const std::string& str)
{
    int n = str.size();
    Node dummy;
    Node** pp = &dummy.next;
    for (int i = 0; i < n; ) {
        auto c = str[i];
        if (c == '-') {
            if (i + 1 < n && str[i+1] == '>') {
                i += 2;
                continue;
            }
        }
        if (std::isdigit(c) || c == '-') {
            int val = c == '-' ? 0 : (c - '0');
            i++;
            while (i < str.size() && std::isdigit(str[i])) {
                val = 10 * val + str[i] - '0';
                i++;
            }
            val = c == '-' ? -val : val;
            *pp = new Node(val);
            pp = &((*pp)->next);
        } else {
            i++;
        }
    }
    return dummy.next;
}

#endif  // LINKED_LIST_INTERNAL_UTIL_H_
