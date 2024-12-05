Given the root of a binary tree, return the postorder traversal of its nodes values.

 

Example 1:

Input: root = [1,null,2,3]

Output: [3,2,1]

Explanation:



Example 2:

Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]

Output: [4,6,7,5,2,9,8,3,1]

Explanation:



Example 3:

Input: root = []

Output: []

Example 4:

Input: root = [1]

Output: [1]

 

Constraints:

The number of the nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100









/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */

/*
this solution is mimic of recursive one
in recursive solution, we have pointer to current line, but in iteration we don;t have it
so to track last line of code, we used last visited node, without this it is not possible to do it

another solution present where 2 stacks are used
https://www.geeksforgeeks.org/iterative-postorder-traversal/
*/
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root)
            return {};

        stack<TreeNode*> s;
       
        TreeNode* last = nullptr;
        vector<int> v;

        // note we are not pushing in advance
        while (root || !s.empty()) { // note or condition
            if(root)
                while(root)
                {
                    s.push(root);
                    root = root->left;
                }
            else
            {
                auto x = s.top(); // we are not popping here, as it could be current node, until we finish visiting right node also
                // we should not pop it
                if(x->right && last != x->right)
                    root = x->right;
                else
                {
                    last = x;
                    v.push_back(x->val);
                    s.pop(); // once the node is visited we pop from stack, means we visited right left both
                    // note we are not assigning root to new top,
                    // it will be done once we are visiting right tree/child
                }
            }

        }

        return v;
    }
};


   1
 2   3
4 5 6 7

4
2
1

pop 4, visit 4, last = 4, root = null
2
1

next itr:
	x = 2 && last == 4 (which is not right of 2)
	so, root = 5
	
next itr:
	push 5, root = null
5
2
1

next itr:
	now top is 5, x = 5
	no right to 5 so visit it, last = 5
	and pop it, root = null
	
next itr:
2    now top is 2, but its right 5 is last visited, so visit 2 now
1

