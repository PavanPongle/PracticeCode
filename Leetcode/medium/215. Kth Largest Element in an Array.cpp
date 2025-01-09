215. Kth Largest Element in an Array

Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?

 

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
 

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104

// using array of k size, and keep array in descending order of sorting
// only work with positive numbers

class Solution {
public:
    int findKthLargest(vector<int>& ve, int k) {

	if(ve.size() == 1)
		return ve[0];
	
        std::vector<int> arr(k, INT_MIN);

        for (int i = 0; i < ve.size(); ++i) {
            int tmp = ve[i];
            for (int j = 0; j < k; ++j) {
                if (arr[j] <= tmp) {
                    swap(tmp, arr[j]);
                }
            }
        }

        return arr[k - 1];
    }
};


using STL
    int findKthLargest(vector<int>& nums, int k) {
        partial_sort(nums.begin(), nums.begin() + k, nums.end(), greater<int>());
        return nums[k - 1];
    }

    int findKthLargest(vector<int>& nums, int k) {
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>());
        return nums[k - 1];
    }
	
//using min heap
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }
};

max-heap using priority_queue

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
		
        for (int i = 0; i < k - 1; i++) {
            pq.pop();
        }
		
        return pq.top();
    }
};