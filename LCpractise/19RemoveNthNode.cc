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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* pb = head;
        ListNode* pf = head;
        while(n > 0 && pf) {pf = pf->next; --n;}
        
        if (n > 0 && pf == NULL) return NULL;
        if (n == 0 && pf == NULL) return pb->next;

        while(pf->next != NULL) {
            pb = pb->next; pf = pf->next;
        }
        pb->next = pb->next->next;
        return head;
    }
};