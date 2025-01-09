Longest Substring Without Repeating Characters

Given a string s, find the length of the longest 
substring
 without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.


//this problem has 2 solution 
// unique char string 
// unique char string length

class Solution {
public:
    // this problem is based on sliding window problem
    // here we need index of start of window, to maintain it we are using map
    // we will store last index of visited char, we should not go for method of
    // tracking frequency counts of method, it will be redudent, instead we
    // should use last index, so that it will indicate it occured and we can
    // track the start of window also
    int lengthOfLongestSubstring(string strs) {

        if (strs.length() <= 1)
            return strs.length();

        int low = -1;                         // start of window
        std::vector<int> occurances(256, -1); // index tracking, ASCII range
        int len = 0;
        std::string s;
        int i = 0;
        for (; i < strs.length(); ++i) {
			// if char is already present, and it's occurance index is more than
            // low then we find duplicates
            if (occurances[strs[i]] > low) // means repetation found after low
            {
                low = occurances[strs[i]]; // get new low of window
                if (len <= i - low) // if length is greater than whatsever we found so far
                {
                    s = strs.substr(low, i - low); // get string
                }
            }
            len = max(len, i - low);
            occurances[strs[i]] = i; // set latest index of char
        }
        return len;
    }
};