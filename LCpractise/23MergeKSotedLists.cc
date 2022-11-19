/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    
// use binary merge
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return 0;
        return mergeKLists(&lists[0], lists.size());
    }
    
private:
    ListNode* mergeKLists(ListNode* lists[], unsigned n) {
        if (n == 0) return 0;
        if (n == 1) return lists[0];
        if (n == 2) {
            return merge2Lists(lists[0], lists[1]);
        }
        ListNode* p1 = mergeKLists(lists, n/2);
        ListNode* p2 = mergeKLists(lists+n/2, n-n/2);
        return merge2Lists(p1, p2);
    }
    
    ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        
        ListNode* r;
        if (l1->val < l2->val) {
            r = l1;
            r->next = merge2Lists(l1->next, l2);
        } else {
            r = l2;
            r->next = merge2Lists(l1, l2->next);
        }
        return r;
        
    }
};