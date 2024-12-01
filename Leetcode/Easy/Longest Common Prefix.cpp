Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
 

Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lowercase English letters.


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {

        size_t minLen = strs[0].length();
        for (size_t i = 1; i < strs.size(); ++i)
        {
            size_t j = 0;
            for (; j < ::min(minLen, strs[i].length()); ++j)
            {
                if (strs[0][j] != strs[i][j])
                {
                    break;
                }
            }
            if (j < minLen)
            {
                minLen = j;
            }

            if(minLen == 0)
                break;
        }

        return  minLen == 0 ? "" : strs[0].substr(0, minLen );
    }
};