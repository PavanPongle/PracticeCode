Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

 

Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]

// Idead is for number position i, we have to find multiplication of all previous numbers and 
// multiplication of post that number and multiply it
// (0 --> i - 1) * 1 * (i + 1 --> n)
// basically we are travelling loop in 2 direction,
// while travelling the array in forward direction we finding pre element multiplication
// while travelling the array in backward direction we finding post element multiplication
// so below solution is combination of 2 direction loop

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

        int n = nums.size();
        vector<int> res(nums.size(), 1);
        int preNumProduct = 1; // product of all previous elements 
        int postNumProduct = 1; // product of all post elements

		// while forward travelling loop we will find product of previous elements
		// and simultaniously, we are multiplying post num product in advance to upcoming elements
        for (int i = 0; i < n; ++i) {
            res[i] *= preNumProduct;
            preNumProduct *= nums[i];

			// here, we are reverse travelling the array and finding post num mul for 0th index (last element to update) 
            res[n - i - 1] *= postNumProduct;
            postNumProduct *= nums[n - i - 1];
        }
        return res;
    }
};