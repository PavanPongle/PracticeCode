Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

 

Example 1:

Input: s = "IceCreAm"

Output: "AceCreIm"

Explanation:

The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".

Example 2:

Input: s = "leetcode"

Output: "leotcede"

 

Constraints:

1 <= s.length <= 3 * 105
s consist of printable ASCII characters.

class Solution {
public:
    string reverseVowels(string s) {

        unordered_set<char> mm = {'A', 'E', 'I', 'O', 'U','a', 'e', 'i', 'o', 'u'};
        
        for (int i = 0, j = s.length() - 1; i < j;) {
            if (mm.find(s[i]) == mm.end())
                ++i;
            else if (mm.find(s[j]) == mm.end())
                --j;
            else {
                swap(s[i], s[j]);
                ++i, --j;
            }
        }
        return s;
    }
};