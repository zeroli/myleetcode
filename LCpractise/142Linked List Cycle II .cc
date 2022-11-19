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
    // assume cycle start at k postion, with the length as L
    // second time meet, one L more steps from p2s after first time meet
    // offset by L, and the meet place is the cycle starts
    ListNode *detectCycle(ListNode *head) {
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
        
        int L = 0;
        while (p1s != p2s || L == 0) {
            p1s = p1s->next;
            p2s = p2s->next->next;
            ++L;
        }
        
        p1s = head;
        ListNode* p1s_f = head;
        for (unsigned int ii = 0; ii < L; ++ii) {
            p1s_f = p1s_f->next;
        }
        while (p1s != p1s_f) {
            p1s = p1s->next; p1s_f = p1s_f->next;
        }
        return p1s;
    }
};