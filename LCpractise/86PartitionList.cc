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
    // find the first node with val>x, and then insert the node with val <x before this node
    ListNode* partition(ListNode* head, int x) {
        if (!head) return head;
        ListNode* fhead = new ListNode(INT_MIN); // assume x > INT_MIN
        fhead->next = head;
        
        // find the pivol, insert after pivol
        ListNode* pivol = fhead;
        while (pivol->next) {
            if (pivol->next->val >= x) break;
            pivol = pivol->next;
        }
        
        if (pivol->next) {
            // go through left to right starting from pivol, and do the insert
            ListNode* previsited = pivol->next;
            ListNode* visiting = previsited->next;
            while(visiting) {
                if (visiting->val < x) {// move it to after pivol, and update pivol
                    ListNode* temp1 = pivol->next;
                    ListNode* temp2 = visiting->next;
                    pivol->next = visiting;
                    pivol = pivol->next;
                    visiting->next = temp1;
                    previsited->next = temp2;
                    visiting = previsited->next;
                } else {
                    previsited = visiting;
                    visiting = visiting->next;
                }
            }
        }
        
        // clean fhead;
        head = fhead->next;
        delete fhead;
        return head;
    }
};