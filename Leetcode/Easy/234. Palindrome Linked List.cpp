Given the head of a singly linked list, return true if it is a 
palindrome
 or false otherwise.

 

Example 1:


Input: head = [1,2,2,1]
Output: true
Example 2:


Input: head = [1,2]
Output: false
 

Constraints:

The number of nodes in the list is in the range [1, 105].
0 <= Node.val <= 9
 

Follow up: Could you do it in O(n) time and O(1) space?

even length
1 2 2 1
^
^

1 2 2 1
  ^
    ^

1 2 2 1 
    ^  
	    ^

Odd length

1 2 3 2 1
^
^

1 2 3 2 1
  ^
    ^

1 2 3 2 1 
    ^  
	    ^
		
		
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
 
// soultion is break in half and reverse the second half 
// then compare it
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        
        if(!head || !head->next)
            return true;

        auto n1 = head;
        auto n2 = head;
        auto p1 = head;

        while(n2 && n2->next) // for even num of list it n1 = NULL and for odd n2->next == NULL
        {
            n1 = n1->next;
            n2 = n2->next->next;            
        }
        p1 = n1; // previous should be at end of loop
        // now n1 is in end of first half (incase of odd length),
        // and at begining of second half for even length  
        // to reverse second half node, move n1 to begining of second half list
        n1 = n1->next;
        p1->next = nullptr; // breaking list
        while(n1)
        {
            auto tmp = n1->next;
            n1->next = p1;
            p1 = n1;
            n1 = tmp;
        }

        // last node is in p1
        n1 = p1;
        n2 = head;
        while(n1)
        {
            if(n1->val != n2->val)
                return false;

            n2 = n2->next;
            n1 = n1->next;
        }

        return true;
    }
};