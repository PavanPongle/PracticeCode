Given a pattern and a string s, find if s follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:

Each letter in pattern maps to exactly one unique word in s.
Each unique word in s maps to exactly one letter in pattern.
No two letters map to the same word, and no two words map to the same letter.
 

Example 1:

Input: pattern = "abba", s = "dog cat cat dog"

Output: true

Explanation:

The bijection can be established as:

'a' maps to "dog".
'b' maps to "cat".
Example 2:

Input: pattern = "abba", s = "dog cat cat fish"

Output: false

Example 3:

Input: pattern = "aaaa", s = "dog cat cat dog"

Output: false

 

Constraints:

1 <= pattern.length <= 300
pattern contains only lower-case English letters.
1 <= s.length <= 3000
s contains only lowercase English letters and spaces ' '.
s does not contain any leading or trailing spaces.
All the words in s are separated by a single space.

class Solution {
public:
    bool wordPattern(string pattern, string s) {

        s.push_back(' '); // to find last word

        unordered_map<char, string> mm;
        unordered_map<string, char> cm; 
        // reverse mapping also require to check if word is already mapped to another char

        // index will run till last of lenght of string 
        // to find last word
        int wordCount = 0;
        for(int i = 0, j = 0, k = 0; i < s.length(); ++i)
        {
            if(s[i] == ' ')
            {
                ++wordCount;
                auto ss = s.substr(j, i - j);
                auto r = mm.find(pattern[k]);
                if(r != mm.end())
                {
                    if(r->second != ss)
                    {
                        return false;
                    }
                    
                }
                else
                {
					//if we find mapping in either map and not in another then it's error
                    if(cm.find(ss) != cm.end())
                        return false;
                    
                    mm[pattern[k]] = ss;
                    cm[ss] = pattern[k];
                }
                j = i+1;
                ++k;
            }
            
        }
        // last check workd cound should match the pattern length
        return wordCount == pattern.length();
    }
};