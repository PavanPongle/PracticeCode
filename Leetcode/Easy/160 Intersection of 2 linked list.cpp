Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.

For example, the following two linked lists begin to intersect at node c1:


The test cases are generated such that there are no cycles anywhere in the entire linked structure.

Note that the linked lists must retain their original structure after the function returns.

Custom Judge:

The inputs to the judge are given as follows (your program is not given these inputs):

intersectVal - The value of the node where the intersection occurs. This is 0 if there is no intersected node.
listA - The first linked list.
listB - The second linked list.
skipA - The number of nodes to skip ahead in listA (starting from the head) to get to the intersected node.
skipB - The number of nodes to skip ahead in listB (starting from the head) to get to the intersected node.
The judge will then create the linked structure based on these inputs and pass the two heads, headA and headB to your program. If you correctly return the intersected node, then your solution will be accepted.

 

Example 1:


Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
- Note that the intersected node's value is not 1 because the nodes with value 1 in A and B (2nd node in A and 3rd node in B) are different node references. In other words, they point to two different locations in memory, while the nodes with value 8 in A and B (3rd node in A and 4th node in B) point to the same location in memory.
Example 2:


Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
Explanation: The intersected node's value is 2 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [1,9,1,2,4]. From the head of B, it reads as [3,2,4]. There are 3 nodes before the intersected node in A; There are 1 node before the intersected node in B.
Example 3:


Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection
Explanation: From the head of A, it reads as [2,6,4]. From the head of B, it reads as [1,5]. Since the two lists do not intersect, intersectVal must be 0, while skipA and skipB can be arbitrary values.
Explanation: The two lists do not intersect, so return null.
 

Constraints:

The number of nodes of listA is in the m.
The number of nodes of listB is in the n.
1 <= m, n <= 3 * 104
1 <= Node.val <= 105
0 <= skipA <= m
0 <= skipB <= n
intersectVal is 0 if listA and listB do not intersect.
intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.
 

Follow up: Could you write a solution that runs in O(m + n) time and use only O(1) memory?



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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // this problem can be solved using 
        // brute force method, using 2 loops to find one common node
        // another is using hash map
        // best one is 2 pointer method, where we bring two pointers
        // at equidistance once either of them reach null;

        ListNode* p1 = headA;
        ListNode* p2 = headB;
        /*
        // this solution works greate but due to cache locality
        // it is not giving one of the best result
        // if we change the order of lines then below algo not working
        while(p1 !=nullptr && p2 !=nullptr && p1 != p2)
        {
            p1 = p1->next;
            p2 = p2->next;

            if(p1 == p2)
                return p1;

            if(p1 ==nullptr)
                p1 = headA;
            
            if(p2 ==nullptr)
                p2 = headB;
        }

        return p1;
        */

        // find lenght of fist list 
        // find lenght of second list
        // based on difference of lenght move either list head pointer
        // compare now

        int l1 = 0;
        while(p1)
        {
            ++l1;
            p1 = p1->next;
        }

        int l2 = 0;
        while(p2)
        {
            ++l2;
            p2 = p2->next;
        }

        if(l1 > l2)
        {
            int diff = l1 - l2;

            p1 = headA;
            while(diff)
            {
                --diff;
                p1 = p1->next;
            }
            p2 = headB;
        }
        else
        {
            int diff = l2 - l1;

            p2 = headB;
            while(diff)
            {
                --diff;
                p2 = p2->next;
            }
            p1 = headA;
        }

        while(p1 != p2)
        {
            p1 = p1->next;
            p2 = p2->next;
        }

        return p1;

    }
};

Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'

for 2 pointer method it has to take below number of rest, and it not in
m + n time complexicity. 

41845 4 1845 41845 41845 41845 41845
56184 5 5618 45561 84556 18455 61845