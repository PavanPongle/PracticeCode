Given two 0-indexed integer arrays nums1 and nums2, return a list answer of size 2 where:

answer[0] is a list of all distinct integers in nums1 which are not present in nums2.
answer[1] is a list of all distinct integers in nums2 which are not present in nums1.
Note that the integers in the lists may be returned in any order.

 

Example 1:

Input: nums1 = [1,2,3], nums2 = [2,4,6]
Output: [[1,3],[4,6]]
Explanation:
For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] = 1 and nums1[2] = 3 are not present in nums2. Therefore, answer[0] = [1,3].
For nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] = 4 and nums2[2] = 6 are not present in nums2. Therefore, answer[1] = [4,6].
Example 2:

Input: nums1 = [1,2,3,3], nums2 = [1,1,2,2]
Output: [[3],[]]
Explanation:
For nums1, nums1[2] and nums1[3] are not present in nums2. Since nums1[2] == nums1[3], their value is only included once and answer[0] = [3].
Every integer in nums2 is present in nums1. Therefore, answer[1] = [].
 
 
 class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        set<int> s1; // note, do not use multiset here
        set<int> s2;

        s1.insert(nums1.begin(), nums1.end());
        s2.insert(nums2.begin(), nums2.end());

        auto first1 = s1.begin();
        auto first2 = s2.begin();
        auto last1 = s1.end();
        auto last2 = s2.end();

        vector<vector<int>> res(2);
        res[0].reserve(nums1.size());
        res[1].reserve(nums2.size());

// add in set and find the intersection of 2 sets, when elements match instead of adding it, skip it
		// add smaller number first then increament counter
		// if both are equal then increament both index
		
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                res[0].push_back(*first1);
                ++first1;
            } else if (*first2 < *first1) {
                res[1].push_back(*first2);
                ++first2;
            } else {
                ++first1;
                ++first2;
            }
        }

        while (first1 != last1) {
            res[0].push_back(*first1);
            ++first1;
        }
        while (first2 != last2) {
            res[1].push_back(*first2);
            ++first2;
        }
        return res;
    }
};


// efficient solution is use benifit of constraint 
// value from -1000 to 1000 means total 2001 elements
class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        vector<int> mark(2001, 0);
        for (const int& num : nums1)
            mark[num + 1000] |= 1; // | is binary or so it will add 01 | 10 = 11
        for (const int& num : nums2)
            mark[num + 1000] |= 2;
        vector<vector<int>> res(2);
		res[0].reserve(nums1.size());
        res[1].reserve(nums2.size());
        for (int num = -1000; num <= 1000; ++num) {
            if (mark[num + 1000] == 3) // present in both, instead of adding we have |  01 | 10 = 11
                continue;
            if (mark[num + 1000] & 1) {
                res[0].push_back(num);
            } else if (mark[num + 1000] & 2)
                res[1].push_back(num);
        }
        return res;
    }
};