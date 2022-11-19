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
// to use constant space, one way is to use merge, 
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        
        int len = 0;
        ListNode* pcur = head;
        while(pcur) {
            pcur = pcur->next;
            ++len;
        }
        ListNode* newhead  = sort(head, len);
        return newhead;
    }
    
private:
    ListNode* sort(ListNode*& head, unsigned len) {
        if (len ==1 ) {
            ListNode* temp = head;
            head = head->next; // this one will move head once for one node
            temp->next = NULL;
            return temp;
        }
        ListNode* left = sort(head, len/2);//head already updated to the len-len/2 th node
        ListNode* right = sort(head, len - len/2);  
        return merge(left, len/2, right, len-len/2);
    }
    
    ListNode* merge(ListNode* l1, unsigned len1, ListNode* l2, unsigned len2) {
        if (!len1) return l2;
        if (!len2) return l1;
        ListNode*  fhead = new ListNode(INT_MIN);
        
        ListNode* pcur = fhead;
        while (!l1 || !l2) {
            int l1val = l1? l1->val : INT_MAX;
            int l2val = l2? l2->val : INT_MAX;
            if (l1val < l2val) {
                pcur->next = l1;
                l1 = l1->next;
            }
            else {
                pcur->next = l2;
                l2 = l2->next;
            }
            pcur = pcur->next;
        }
        ListNode* head = fhead->next;
        delete fhead;
        return head;
    }
    
    /* this one works
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        
        vector<int> vval;
        ListNode* pcur = head;
        while(pcur) {
            vval.push_back(pcur->val);
            pcur = pcur->next;
        }
        sort(vval.begin(), vval.end());
        
        pcur = head;
        int idx = 0;
        while(pcur) {
            pcur->val = vval[idx];
            pcur = pcur->next; ++idx;
        }
        return head;
    }
    */
};