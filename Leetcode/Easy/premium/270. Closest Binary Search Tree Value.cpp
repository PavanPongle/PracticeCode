Given the root of a binary search tree and a target value, return the value in the BST that is closest to the target. If there are multiple answers, print the smallest.

 

Example 1:



Input: root = [4,2,5,1,3], target = 3.714286
Output: 4
Example 2:

Input: root = [1], target = 4.428571
Output: 1

We can rewrite the recursive function in an iterative form, using a loop to simulate the recursive process. We start from the root node and check whether the absolute difference between the current node's value and the target value is less than the current minimum difference. If it is, we update the answer. Then, based on the size relationship between the target value and the current node's value, we decide to move to the left subtree or the right subtree. The loop ends when we traverse to a null node.


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
    int closestValue(TreeNode* root, double target) {
        int ans = root->val;
        double diff = INT_MAX;
        while (root) {
            double nxt = abs(root->val - target);
            if (nxt < diff || (nxt == diff && root->val < ans)) {
                diff = nxt;
                ans = root->val;
            }
            root = target < root->val ? root->left : root->right;
        }
        return ans;
    }
};