Given two integer arrays nums1 and nums2, return an array of their 
intersection
. Each element in the result must be unique and you may return the result in any order.

 

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Explanation: [4,9] is also accepted.
 

Constraints:

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000 

class Solution {
public:
    vector<int> intersection(const vector<int>& nums1,
                             const vector<int>& nums2) {
        bitset<1001> b = 0; // use bitset instead of set to save memory

        const vector<int>* smaller = nullptr;
        const vector<int>* bigger = nullptr;
        if (nums1.size() < nums2.size()) {
            smaller = &nums1;
            bigger = &nums2;
        } else {
            bigger = &nums1;
            smaller = &nums2;
        }

        for (auto x : *smaller)
            b[x] = 1;

        vector<int> res;
        res.reserve(smaller->size());

        for (auto x : *bigger) {
            if (b[x]) {
                res.push_back(x);
                b[x] = 0;
            }
        }

        return res;
    }
};