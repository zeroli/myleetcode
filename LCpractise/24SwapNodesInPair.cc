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
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode* fhead = new ListNode(INT_MIN);
        fhead->next = head;
        
        ListNode* pre = fhead;
        ListNode* first = fhead->next;
        ListNode* second = first->next;
        
        while (first && second) {
            pre->next = second;
            first->next = second->next;
            second->next = first;
            
            pre = first;
            first = pre->next;
            if (first) second = first->next;
        }
        head = fhead->next;
        delete fhead;
        return head;
    }
};