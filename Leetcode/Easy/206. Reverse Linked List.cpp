206. Reverse Linked List


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        
        if(!head || !head->next)
            return head;

        ListNode* h1 = head;
        ListNode* p = nullptr; // without previous init to nullptr, we will not get hint how to start
        while(head)
        {
            auto tmp = head->next; // this is imp, we are breaking link to next so store it before lost
            head->next = p;
            p = head;
            head = tmp;
        } 
        return p; // note, we are returning the previous value not temp/head value
    }
};