Two strings are considered close if you can attain one from the other using the following operations:

Operation 1: Swap any two existing characters.
For example, abcde -> aecdb
Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.

 

Example 1:

Input: word1 = "abc", word2 = "bca"
Output: true
Explanation: You can attain word2 from word1 in 2 operations.
Apply Operation 1: "abc" -> "acb"
Apply Operation 1: "acb" -> "bca"
Example 2:

Input: word1 = "a", word2 = "aa"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.
Example 3:

Input: word1 = "cabbba", word2 = "abbccc"
Output: true
Explanation: You can attain word2 from word1 in 3 operations.
Apply Operation 1: "cabbba" -> "caabbb"
Apply Operation 2: "caabbb" -> "baaccc"
Apply Operation 2: "baaccc" -> "abbccc"

//Note, presence of a char in both word should be same either both 0 or non zero

class Solution {
public:
    bool closeStrings(string word1, string word2) {

        if (word1.length() != word2.length())
            return false;

        vector<int> freq1(26, 0);
        vector<int> freq2(26, 0);

        vector<int> char_present1(26, 0);
        vector<int> char_present2(26, 0);

        for (auto x : word1) {
            char_present1[x - 'a'] = 1;
            ++freq1[x - 'a'];
        }

        for (auto x : word2) {
            char_present2[x - 'a'] = 1;
            ++freq2[x - 'a'];
        }

        // in one word the char is present and in another if not
        //  present then it is fail
        if (char_present1 != char_present2)
            return false;

		// Note we are not checking the frequencies of char by char
		// we are checking occurrences of frequencies 
        sort(freq1.begin(), freq1.end());
        sort(freq2.begin(), freq2.end());

        if (freq1 != freq2) {
            return false;
        }

        return true;
    }
};