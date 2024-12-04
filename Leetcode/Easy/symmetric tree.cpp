Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

 

Example 1:


Input: root = [1,2,2,3,4,4,3]
Output: true
Example 2:


Input: root = [1,2,2,null,3,null,3]
Output: false
 

Constraints:

The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100
 

Follow up: Could you solve it both recursively and iteratively?


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
class Solution {
public:

    /* Iterative Postorder Traversal to check if two binary
     * trees are identical */
    bool isMirror(TreeNode* r1, TreeNode* r2) {
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
                r2 = r2->right;
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
            r2 = r2->left;
        }
        // both trees are identical
        return true;
    }

    // in case of same tree, we pass: left, left or right, right in recursion
    // but incase of mirror we pass: right, left or left, right
    // Note the difference
    bool isMirror(TreeNode* p, TreeNode* q) {
        if(!p && !q)    return true; // both are null
        if(!p || !q)    return false; // either is null
        return (p->val==q->val) && 
                isMirror(p->left, q->right) &&
                isMirror(p->right, q->left);
    }

    bool isSymmetric(TreeNode* root) {
        if(!root)
            return true;
        return isMirror(root->left, root->right);    
    }
};