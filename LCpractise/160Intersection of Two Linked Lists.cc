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
    int getLength(ListNode* head){
        int L = 0;
        while(head != NULL) {head = head->next; ++L;}
        return L;
    }

    // find the length difference, and shift the start point of the longer one
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL) return NULL;
        
        int LA = getLength(headA);
        int LB = getLength(headB);
        ListNode* RA = headA;
        ListNode* RB = headB;
        int dL = max(LA, LB) - min(LA, LB);
        if (LA < LB) swap(RA, RB); // RA is the non-shorter one
        for (int ii = 0; ii < dL; ++ii) RA = RA->next;
        for (int ii = 0; ii < min(LA, LB); ++ii) {
            if (RA != RB) {RA = RA->next; RB = RB->next;}
            else {break;}
        }
        if (RA == RB) return RA;
        return NULL;
    }
};