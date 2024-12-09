Given two strings s and t, return true if t is an 
anagram
 of s, and false otherwise.

 

Example 1:

Input: s = "anagram", t = "nagaram"

Output: true

Example 2:

Input: s = "rat", t = "car"

Output: false

 

Constraints:

1 <= s.length, t.length <= 5 * 104
s and t consist of lowercase English letters.
 

Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?

This idea uses a hash table to record the times of appearances of each letter in the two strings s and t. For each letter in s, it increases the counter by 1 while for each letter in t, it decreases the counter by 1. Finally, all the counters will be 0 if they two are anagrams of each other.

class Solution {
public:
    bool isAnagram(string s, string t) {
        
        if(s.empty() || t.empty())
            return false;

        if(s.length() != t.length())
            return false;

        int ss[26];

        for(int i =0 ; i < 26 ; ++i)
            ss[i] = 0;

        for(int i = 0 ; i < s.length() ; ++i)
        {
            ss[s[i] - 'a']++;
            ss[t[i] - 'a']--;
        }

        for(int i =0 ; i < 26 ; ++i)
            if(ss[i] != 0)
                return false;

        return true;
    }
};