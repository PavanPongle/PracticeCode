Given the root of a binary tree, return all root-to-leaf paths in any order.

A leaf is a node with no children.

 

Example 1:


Input: root = [1,2,3,null,5]
Output: ["1->2->5","1->3"]
Example 2:

Input: root = [1]
Output: ["1"]
 

Constraints:

The number of nodes in the tree is in the range [1, 100].
-100 <= Node.val <= 100


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
    vector<string> binaryTreePaths(TreeNode* root) {

        vector<string> ss;
        if(!root)
            return ss;

		// instead of taking 2 stacks, we could have taken one stack with custom data having {TreeNode*, val}
        stack<TreeNode*> s;
        stack<string> path;
		
        s.push(root);
        path.push(to_string(root->val));


        while(!s.empty())
        {
            root = s.top();
            s.pop();

            string p = path.top();
            path.pop();

            if(root->left == nullptr && root->right == nullptr)
            {
                ss.push_back(p);
                continue;
            }

            if(root->left)
            {
                s.push(root->left);
                path.push(p + "->" + to_string(root->left->val));
            }
            
            if(root->right)
            {
                s.push(root->right);
                path.push(p + "->" + to_string(root->right->val));
            }
        }
        return ss;
    }
};