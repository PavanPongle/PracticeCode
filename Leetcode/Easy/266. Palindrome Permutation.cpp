Given a string s, return true if a permutation of the string could form a palindrome and false otherwise.

 

Example 1:

Input: s = "code"
Output: false
Example 2:

Input: s = "aab"
Output: true
Example 3:

Input: s = "carerac"
Output: true

If a string is a palindrome, at most one character can appear an odd number of times, while all other characters must appear an even number of times. Therefore, we only need to count the occurrences of each character and then check if this condition is satisfied.

class Solution {
public:
    bool canPermutePalindrome(string s) {
        vector<int> cnt(26);
        for (char& c : s) {
            ++cnt[c - 'a'];
        }
        int odd = 0;
        for (int x : cnt) {
            odd += x & 1;
        }
        return odd < 2;
    }
};