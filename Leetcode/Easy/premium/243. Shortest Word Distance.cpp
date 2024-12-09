Given an array of strings wordsDict and two different strings that already exist in the array word1 and word2, return the shortest distance between these two words in the list.

 

Example 1:

Input: wordsDict = ["practice", "makes", "perfect", "coding", "makes"], word1 = "coding", word2 = "practice"
Output: 3
Example 2:

Input: wordsDict = ["practice", "makes", "perfect", "coding", "makes"], word1 = "makes", word2 = "coding"
Output: 1
 

Constraints:

2 <= wordsDict.length <= 3 * 104
1 <= wordsDict[i].length <= 10
wordsDict[i] consists of lowercase English letters.
word1 and word2 are in wordsDict.
word1 != word2


class Solution {
public:
    int shortestDistance(vector<string>& wordsDict, string word1, string word2) {
        int ans = INT_MAX;
        for (int k = 0, i = -1, j = -1; k < wordsDict.size(); ++k) {
            if (wordsDict[k] == word1) {
                i = k;
            }
            if (wordsDict[k] == word2) {
                j = k;
            }
            if (i != -1 && j != -1) {
                ans = min(ans, abs(i - j));
            }
        }
        return ans;
    }
};