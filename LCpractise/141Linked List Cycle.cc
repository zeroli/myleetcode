/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
// use two runners
    bool hasCycle(ListNode *head) {
        if (head == NULL) return head;
        if (head->next == NULL) return NULL;
        
        int D = 0;
        ListNode* p1s = head;
        ListNode* p2s = head;
        while (D == 0 || (p1s != p2s && p1s != NULL && p2s != NULL && p2s->next != NULL) ) {
            p1s = p1s->next;
            p2s = p2s->next->next;
            ++D;
        }
        if (p1s == NULL || p2s == NULL || p2s->next == NULL) return NULL;
        return true;
    }
};