Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: 2
Example 2:

Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5
 

Constraints:

The number of nodes in the tree is in the range [0, 105].
-1000 <= Node.val <= 1000



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
// this problem can be solved using DFS and BFS
// in BFS, if we encouter a level where node does not have childern then stop
// in DFS, we will go to each node and take min among (depth till and for this node)
    int recursive(TreeNode* root)
    {
        if(root == nullptr)
            return 0;

        int lht = recursive(root->left);
        int rht = recursive(root->right);

        // we will not take min if either child node is not present
        if(lht == 0)
            return 1+rht;

        if(rht == 0)
            return 1+lht;

        int low  = min(lht, rht);

        return low + 1;
    }

    int minDepth(TreeNode* root) {
        return recursive(root);
    }
};