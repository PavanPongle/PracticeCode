Given an integer array nums where the elements are sorted in ascending order, convert it to a 
height-balanced
 binary search tree.

 

Example 1:


Input: nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: [0,-10,5,null,-3,null,9] is also accepted:

Example 2:


Input: nums = [1,3]
Output: [3,1]
Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.
 

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums is sorted in a strictly increasing order.



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

 To create a height-balanced binary search tree (BST) from a sorted array, we need to maintain an equal depth across the tree, so both left and right subtrees are as close in height as possible. The best way to achieve this is by choosing the middle element of the array as the root, ensuring the left half of the array will form the left subtree and the right half will form the right subtree. Recursively applying this approach ensures the resulting tree is both height-balanced and sorted according to BST properties.
 */
class Solution {
public:

    TreeNode* RecursiveFun(vector<int>& nums, int low, int high)
    {
        if(low > high)
            return nullptr;

        int mid = low + (high - low)/2;

        // This can be solved using non recursive
        // have stack of custom data, having TreeNode, low and high
        // have a stack and add a root node, and while (!stack.empty())
        // if low > high then pop from stack
        // create new node and have value at index mid
        // push in stack, mid + 1, high for right node
        // new low = low and high = mid -1 (for left node) 
        // go to begining of loop again

        TreeNode* root = new TreeNode(nums[mid]);
        root->left = RecursiveFun(nums, low, mid -1);
        root->right = RecursiveFun(nums, mid +1, high);
        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int low  = 0 ;
        int high = nums.size() -1;

        return RecursiveFun(nums, low, high);
    }
};