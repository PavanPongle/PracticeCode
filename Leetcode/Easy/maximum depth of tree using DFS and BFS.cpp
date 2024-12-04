Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: 3
Example 2:

Input: root = [1,null,2]
Output: 2
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
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
class Solution {
public:
    int maxDepth(TreeNode* root) {

        if (root == nullptr)
            return 0;

        int depth = 0;
        // this can be solved using DFS or BFS
        if (0) {
            // lets try with BFS
            queue<TreeNode*> q;

            q.push(root);

            while (!q.empty()) {
                ++depth; // level

                int child_nodes = q.size();
                // lets visit all child nodes then only inc the deapth
                for (int i = 0; i < child_nodes; ++i) {
                    TreeNode* f = q.front();
                    q.pop();

                    if (f->left)
                        q.push(f->left);
                    if (f->right)
                        q.push(f->right);
                }
            }
        }else
        {
            //using DFS

            stack<pair<TreeNode*,int>> stk;
            stk.push({root, 1});
            int len = 1;

            // code is similar to recursion, just used the stack and checked if not empty
            // visit left
            // visit current
            // visit right
            while(!stk.empty())
            {
                auto f = stk.top();
                stk.pop();

                len = max(len, f.second);

                if(f.first->left) stk.push({f.first->left, f.second + 1});
                if(f.first->right) stk.push({f.first->right, f.second +  1});
            }
            return len;


        }
        return depth;
    }
};