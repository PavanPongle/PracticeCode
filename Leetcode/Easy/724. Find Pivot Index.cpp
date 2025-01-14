Given an array of integers nums, calculate the pivot index of this array.

The pivot index is the index where the sum of all the numbers strictly to the left of the index is equal to the sum of all the numbers strictly to the index's right.

If the index is on the left edge of the array, then the left sum is 0 because there are no elements to the left. This also applies to the right edge of the array.

Return the leftmost pivot index. If no such index exists, return -1.

 

Example 1:

Input: nums = [1,7,3,6,5,6]
Output: 3
Explanation:
The pivot index is 3.
Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
Right sum = nums[4] + nums[5] = 5 + 6 = 11
Example 2:

Input: nums = [1,2,3]
Output: -1
Explanation:
There is no index that satisfies the conditions in the problem statement.
Example 3:

Input: nums = [2,1,-1]
Output: 0
Explanation:
The pivot index is 0.
Left sum = 0 (no elements to the left of index 0)
Right sum = nums[1] + nums[2] = 1 + -1 = 0

// this can be solved using 2 pointer from low --> <--- high
// iterate and inc low if prefix sum is smaller than right end sum so far
// dec high if right end sum is smaller than left end sum so far

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int l_sum = 0;
        int r_sum = accumulate(nums.begin(), nums.end(), 0);

        //use of left and right prefix sum
        int i = 0, j = nums.size() -1;
        for(auto i = 0 ; i < nums.size(); ++i)
        {
            int curr = nums[i];

            r_sum -= nums[i];

            if(r_sum == l_sum)
            {
                return i;
            }            

            l_sum += nums[i];
        }
        return -1;
    }
};