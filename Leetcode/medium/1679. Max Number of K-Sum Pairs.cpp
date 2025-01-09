You are given an integer array nums and an integer k.

In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.

Return the maximum number of operations you can perform on the array.

 

Example 1:

Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.
Example 2:

Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.
 
 
 class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
// best performed is logic 2 over large size of array
// logic 1.
// while traversing the nums, check if k -x number available,
// if so then it is pair and decrese the frequency count of k - x
// else add x in map and increase its frequency
        int count = 0;
        // unordered_map<int, int> mm;
        // mm.reserve(nums.size());
        // for (auto x : nums) {
        //     if (mm[k - x] > 0) {
        //         --mm[k - x];
        //         count++;
        //     } else
        //         ++mm[x];
        // }

// logic 2.
// sort the array
// use two pointers, and go on fiding sum of 2 numbers equal to k, 
// if sum less than k then increase the left index, else decrease right index
        sort(nums.begin(), nums.end());
        for(int i = 0, j = nums.size() - 1; i < j ;)
        {
            if(nums[i] + nums[j] == k)
            {
                ++count;
                ++i;
                --j;
            }
            else if(nums[i] + nums[j] > k)
            {
                --j;
            }
            else
            {
                ++i;
            }
        }

//this logic does not work yet, 
// where we can travel k/2 loop , assuming nothing is missing from 1 to k in array
        // for (auto x : nums)
        //     ++mm[x];

        // for (int i = 1; i <= (k / 2); ++i) {
        //     auto it1 = mm.find(i);
        //     if (it1 == mm.end())
        //         continue;

        //     auto it2 = mm.find(k - i);
        //     if (it2 == mm.end())
        //         continue;

        //     if (i == k - i) {
        //         count += mm[k - i] / 2;
        //     } else
        //         count += min(mm[i], mm[k - i]);
        // }

        return count;
    }
};