You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

 

Example 1:


Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
Example 2:

Input: list1 = [], list2 = []
Output: []
Example 3:

Input: list1 = [], list2 = [0]
Output: [0]

Constraints:

The number of nodes in both lists is in the range [0, 50].
-100 <= Node.val <= 100
Both list1 and list2 are sorted in non-decreasing order.


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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
        if(!list1)
            return list2;
        else if(!list2)
            return list1;

        ListNode* list3 = nullptr;
        if(list1 -> val > list2 -> val)
        {
            list3 = list2;
            list2 = list2 -> next;
        }
        else
        {
            list3 = list1;
            list1 = list1 -> next;
        }

        //need pointer to head to return 
        ListNode* list4 = list3;
        while(list1 && list2)
        {
            if(list1->val < list2->val)
            {
                list3->next = list1;
                list1 = list1->next;
            }
            else
            {
                list3->next = list2;
                list2 = list2->next;
            }
            list3 = list3->next;
        }

        if(list1)
        {
            if(!list3)
                list3 = list1;
            else
                list3->next = list1;
        }

        if(list2)
        {
            if(!list3)
                list3 = list2;
            else
                list3->next = list2;
        }
        return list4;
    }
};