Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.

Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

 

Example 1:

Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.
Example 2:

Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.
Example 3:

Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.

// This problem is of sliding window pattern
//

class Solution {
public:
    int maxVowels(string s, int k) {
        
        int currSum = 0;
        int maxSum = 0;

        unordered_set<char> mm = {'a', 'e', 'i', 'o', 'u'};
        for(int i = 0 ; i < k; ++i)
            if(mm.find(s[i]) != mm.end())
                ++currSum;

        maxSum = currSum;
        for(int i = k ; maxSum != k && i < s.length(); ++i)
        {
			//If current char is vowels then inc count of vowels found so far
            if(mm.find(s[i]) != mm.end())
                ++currSum;
			
			//as it is fixed size window,  check at begin if it was vowel then decrease  the count
            if(mm.find(s[i - k]) != mm.end())
                --currSum;
            
            if(maxSum < currSum)
                maxSum = currSum;
        }

        return maxSum;
    }
};