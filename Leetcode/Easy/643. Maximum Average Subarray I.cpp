ou are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.

 

Example 1:

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75
Example 2:

Input: nums = [5], k = 1
Output: 5.00000

// sliding window example
// fixed size window

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        if (nums.size() < k)
            return 0.0;

        double maxSum = 0;
        double currSum = 0;

        for (int i = 0; i < k; ++i)
            currSum += nums[i];

        maxSum = currSum;
        for (int i = k; i < nums.size(); ++i) {
            currSum += nums[i] - nums[i - k]; // as it is fixed size,  so add current element and remove the first one in window
            if (maxSum < currSum) {
                maxSum = currSum;
            }
        }
        return (maxSum / k);
    }
};