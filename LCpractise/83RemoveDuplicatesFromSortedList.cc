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
        if (head == NULL || head->next == NULL) return head;
        
        ListNode* firstInst = head;
        ListNode* lastInst = head;
        while (firstInst != NULL) {// loop through list
            while (lastInst->next != NULL && lastInst->next->val == lastInst->val) { // loop to find the duplicaiton one
                lastInst = lastInst->next;
            }
            firstInst->next = lastInst->next;
            firstInst = lastInst->next;
            lastInst = firstInst;
        }
        
        return head;
    }
};