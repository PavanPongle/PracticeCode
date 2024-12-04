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

/* recursion
 if(curr == null)
    return;

    visit(curr->left); // go to left most
    print curr->val;  // visit it
    visit(curr->right); // now go to right most

    if we have hint of right node we can avoid stack
    https://www.geeksforgeeks.org/threaded-binary-tree/


*/
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        
        stack<TreeNode*> mstack;

        vector<int> res;
        TreeNode* curr  = root;

        // Hint , below function is similar to recursive one
        while(curr || mstack.empty() == false)
        {
            while(curr)
            {
                //traverse to left most node
                mstack.push(curr);
                curr = curr->left;
            }

            //now left most node reached and curr is null
            curr = mstack.top();
            mstack.pop();

            // visit node when no left node
            res.push_back(curr->val);

            //traverse to right node, use same loop, as in recursion we use same fun
            curr = curr->right;         
        }
        return res;
    }
};