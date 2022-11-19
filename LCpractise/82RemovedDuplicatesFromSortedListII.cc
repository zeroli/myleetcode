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
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* fhead = new ListNode(INT_MIN);
        fhead->next = head;
        
        ListNode* ppre = fhead;
        ListNode* pcur = head;
        while (pcur) {
            int count = 0;
            while (pcur->next && pcur->next->val == pcur->val) {
                pcur = pcur->next;
                ++count;
            }
            if (!count) {//no duplciation
                ppre = pcur;
            }
            else {//duplication
                ppre->next = pcur->next;
            }
            pcur = pcur->next;
        }
        
        head = fhead->next;
        
    }
};