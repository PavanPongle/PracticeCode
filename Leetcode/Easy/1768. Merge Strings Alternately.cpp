You are given two strings word1 and word2. Merge the strings by adding letters in alternating order, starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string.

Return the merged string.

 

Example 1:

Input: word1 = "abc", word2 = "pqr"
Output: "apbqcr"
Explanation: The merged string will be merged as so:
word1:  a   b   c
word2:    p   q   r
merged: a p b q c r
Example 2:

Input: word1 = "ab", word2 = "pqrs"
Output: "apbqrs"
Explanation: Notice that as word2 is longer, "rs" is appended to the end.
word1:  a   b 
word2:    p   q   r   s
merged: a p b q   r   s
Example 3:

Input: word1 = "abcd", word2 = "pq"
Output: "apbqcd"
Explanation: Notice that as word1 is longer, "cd" is appended to the end.
word1:  a   b   c   d
word2:    p   q 
merged: a p b q c   d

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string s;
        s.reserve(word1.length() + word2.length());
        int m = min(word1.length(), word2.length());
        string* maxs = word1.length() > word2.length() ? &word1 : &word2;

        for(int i = 0 ; i < m; ++i)
        {
            s+= word1[i];
            s+= word2[i];
        }

        for(int i = m ; i < maxs->length(); ++i)
            s+= (*maxs)[i];

        return s;
    }
};	