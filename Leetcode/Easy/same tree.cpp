Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

 

Example 1:


Input: p = [1,2,3], q = [1,2,3]
Output: true
Example 2:


Input: p = [1,2], q = [1,null,2]
Output: false
Example 3:


Input: p = [1,2,1], q = [1,1,2]
Output: false
 

Constraints:

The number of nodes in both trees is in the range [0, 100].
-104 <= Node.val <= 104


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// Note; this can also be solved using tree traversal and comparing their results
// like in order traversal
class Solution {
public:

    /* Iterative Postorder Traversal to check if two binary
     * trees are identical */
    bool isSame(TreeNode* r1, TreeNode* r2) {
        stack<TreeNode*> stack1, stack2;

        // loop until both trees are completely traversed
        while (r1 != NULL || !stack1.empty() || r2 != NULL || !stack2.empty()) {
            // push all left nodes of first tree in stack1
            while (r1 != NULL) {
                stack1.push(r1);
                r1 = r1->left;
            }
            // push all left nodes of second tree in stack2
            while (r2 != NULL) {
                stack2.push(r2);
                r2 = r2->left;
            }
            // if size of both stacks is different, trees are
            // not identical
            if (stack1.size() != stack2.size())
                return false;
            // pop one node from each stack and compare their
            // data
            r1 = stack1.top();
            stack1.pop();
            r2 = stack2.top();
            stack2.pop();
            if (r1->val != r2->val)
                return false;
            // move to the right of the popped nodes
            r1 = r1->right;
            r2 = r2->right;
        }
        // both trees are identical
        return true;
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p && !q)    return true; // both are null
        if(!p || !q)    return false; // either is null
        return p->val==q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};