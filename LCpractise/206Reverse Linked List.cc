/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 // revert one by one, use a fake pre-head node to turn the head into a normal node, and delete it late
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        
        // fake head 
        ListNode* fhead = new ListNode(INT_MIN);
        fhead->next = head;
        
        // revert one, and keep a recover of next
        ListNode* pcur= head;
        ListNode* ppre = fhead;
        while (pcur) {
            ListNode* pnext = pcur->next;
            pcur->next = ppre;
            ppre = pcur;
            pcur = pnext;
        }
        head->next = NULL;
        delete fhead;
        return ppre;
    }
};