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
// use carryover
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carryover) {
        if (l1 == NULL && l2 == NULL && !carryover) return NULL;
        if (l1 == NULL && l2 == NULL && carryover) return new ListNode(carryover);
        
        int a = l1? l1->val : 0;
        int b = l2? l2->val : 0;
        int sum = a + b + carryover;
        ListNode* sumh = new ListNode(sum%10);
        carryover = sum/10? 1:0;
        sumh->next = addTwoNumbers(l1? l1->next : NULL, l2? l2->next : NULL, carryover);
    }
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return addTwoNumbers(l1, l2, 0);
    }
};