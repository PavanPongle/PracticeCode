Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2
 

Constraints:

1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107




There are varities of problem for finding total subarray and max length subarray, both are different and 
approach also different.

current problem is no max subarrays, just subarray

BF

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        
        int sum = 0;
        int cnt = 0;

        for(int i = 0 ; i< nums.size() ; ++i)
        {
            sum = 0;
            for(int j = i ; j < nums.size() ; ++j)
            {
                sum += nums[j];                 
                if(k == sum)
                    cnt++;
            }

        }

        return cnt;
    }
};


//hash map

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        
        // map of prefix sum vs frequency of it
        map<int, int> mm;
        int sum = 0; // initial sum is 0, it is prefix
        int ans = 0; // variable to total count of subarrays
        mm[sum] = 1; // when sum = 0, such possiblity is 1 , precondition
        for(auto x : nums)
        {
            // calculate prefix till current element
            sum += x;

            // check for possiblity of having another subarray in past
            // which gives target = current prefix - some last sub array prefix 
            int f = sum - k;

            if(mm.find(f) != mm.end())
            {
                // if we find such sub array in past which value
                // will help us to get target when (k = sum - f)
                ans += mm[f];
            }
            mm[sum]++; // Note we are increasing frequency
        }

        return ans;
    }
};

// same pattern can be used to store the index of prefix sum
// so when we found sum, we can find the total number in that range [last sum's index , curent range]

3.
// when we have to find the max element subarray
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        
        // map of prefix sum vs index of it
        map<int, int /*index*/> mm;
		
        int sum = 0; // initial sum is 0, it is prefix
        int ans = 0; // variable to total count of subarrays
        mm[sum] = -1; // when sum = 0, such possiblity is 1 , precondition
        for(auto x : nums)
        {
            // calculate prefix till current element
            sum += x;

			if(k == sum)
				ans = max(ans, i + 1);

            // check for possiblity of having another subarray in past
            // which gives target = current prefix - some last sub array prefix 
			// [ [sum - k][ k ] ]
			//   current prefix
            int f = sum - k;

            if(mm.find(f) != mm.end())
            {
                // if we find such sub array in past which value
                // will help us to get target when (k = sum - f)
                ans = max(ans, i - mm[f]);
            }
            mm[sum] = i; // Note we are storing index here
        }

        return ans;
    }
};