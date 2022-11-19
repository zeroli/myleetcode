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
// form a cycle, and cut in the middle
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || k==0) return head;
        ListNode* pcur = head;
        int len = 1;
        while (pcur->next) {
            pcur = pcur->next;
            ++len;
        }
        
        k %= len;
        if (k==0) return head;
        k = len - k;
        
        pcur->next = head;
        pcur = head;
        while (k>1) {
            pcur = pcur->next;
            --k;
        }
        ListNode* newhead = pcur->next;
        pcur->next = NULL;
        return newhead;
    }
};