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
    ListNode* removeElements(ListNode* head, int val) {
        if (head == NULL) return NULL;
        while (head != NULL && head->val == val) {head = head->next;}
        if (head == NULL) return NULL;
        
        ListNode* pre = head;
        ListNode* cur = head->next;
        while (cur != NULL){
            while (cur != NULL && cur->val == val) {cur = cur->next;}
            pre->next = cur;
            if (cur != NULL) {
                pre = cur;
                cur = cur->next;
            }
        }
        return head;
    }
};