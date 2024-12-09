Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.

 

Example 1:

Input: nums = [1,2,3,1], k = 3
Output: true
Example 2:

Input: nums = [1,0,1,1], k = 1
Output: true
Example 3:

Input: nums = [1,2,3,1,2,3], k = 2
Output: false
 

Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
0 <= k <= 105


class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        
        unordered_map<int, int> mm;

        for(int i =0 ; i < nums.size(); ++i)
        {
            if(mm.find(nums[i]) == mm.end())
                mm[nums[i]] = i;
            else
            { 
                if((i - mm[nums[i]]) <= k ) // check the diff with last index of element
                    return true;
                else
                    mm[nums[i]] = i; // update the recent value to find min diff
            }
        }

        return false;
    }
};

// note we have to find index for matching this condition
// abs(i - j) <= k.
// min diff, not max