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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL && l2 == NULL) return NULL;
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;
        
        ListNode* c1 = l1;
        ListNode* c2 = l2;
        ListNode* ml = l1;
        if (c2->val < c1->val) ml = l2;
        
        while (c1 != NULL && c2 != NULL) {//c1 and c2 always points to the remain not merged
            if (c2->val >= c1->val) {// take c1 in and move c1 forward
                ListNode* pre_c1;
                while (c1 != NULL && c2->val >= c1->val) {
                    pre_c1 = c1;
                    c1 = c1->next;
                }
                pre_c1->next = c2; // take c2 in
                if (c2->next == NULL) { c2->next = c1; break;}// if one reaches end
                if (c1 == NULL || c2->next->val < c1->val) {// update c2->next and c2
                    c2 = c2->next;
                }
                else {
                    ListNode* post_c2 = c2->next;
                    c2->next = c1;
                    c2 = post_c2;
                }
            }
            else {
                ListNode* pre_c2;
                while(c2 != NULL && c2->val < c1->val) {
                    pre_c2 = c2;
                    c2 = c2->next;
                }
                pre_c2->next = c1;
                if (c1->next == NULL) { c1->next = c2; break; } // if one reaches end
                if (c2 == NULL || c1->next->val <= c2->val) {// update c1->next and c1
                    c1 = c1->next;
                }
                else {
                    ListNode* post_c1 = c1->next;
                    c1->next = c2;
                    c1 = post_c1;
                }
            }
        }
        
        return ml;
    }
};