


Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

 

Example 1:

Input: s = "egg", t = "add"

Output: true

Explanation:

The strings s and t can be made identical by:

Mapping 'e' to 'a'.
Mapping 'g' to 'd'.
Example 2:

Input: s = "foo", t = "bar"

Output: false

Explanation:

The strings s and t can not be made identical as 'o' needs to be mapped to both 'a' and 'r'.

Example 3:

Input: s = "paper", t = "title"

Output: true

 

Constraints:

1 <= s.length <= 5 * 104
t.length == s.length
s and t consist of any valid ascii character.


class Solution {
public:
    bool isIsomorphic(string s, string t) {
        
        if(s.length() != t.length())
            return false;

	unordered_map<char, char> mm;
	unordered_set<char> alreadyMapped;

	for(int i = 0 ; i < s.length(); ++i)
	{
		if(mm.find(s[i]) == mm.end() && alreadyMapped.find(t[i]) == alreadyMapped.end())
		{
		    mm[s[i]] = t[i];
			alreadyMapped.insert(t[i]);
		}
		else if(mm[s[i]] != t[i])
			return false;
	}
        
        return true;
    }
};


use of array beasts 100%
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        
        if(s.length() != t.length())
            return false;

    vector<int> mm(256,-1); // note int mm[256] = {-1} did not init all values to -1, so used vector
    vector<int> alreadyMapped(256,-1);

	for(int i = 0 ; i < s.length(); ++i)
	{
		if(mm[s[i]] == -1 && alreadyMapped[t[i]] == -1)
		{
		    mm[s[i]] = t[i];
			alreadyMapped[t[i]] = 1;
		}
		else if(mm[s[i]] != t[i])
			return false;
	}
        
        return true;
    }
};