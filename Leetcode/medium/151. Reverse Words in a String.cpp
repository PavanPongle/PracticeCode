Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

 

Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
 
 
class Solution {
public:
    string reverseWords(string s) {

        reverse(s.begin(), s.end());
        int n = s.size();
        int left = 0;  // to track for begin of word
        int right = 0; // to track end of word
        int i = 0; // to iterate over the string
        while (i < n) {
			//find first char, continue until white space
            while (i < n && s[i] == ' ')
                i++;
			//if end of string break
            if (i == n)
                break;
			// now shift word to eliminate the whitespace at begining
            while (i < n && s[i] != ' ') {
                s[right++] = s[i++];
            }
			
			//reverse the string 
            reverse(s.begin() + left, s.begin() + right);
			
			// append the white space at end of word
            s[right++] = ' ';
			
			// now last word ending + while space become new location of work start
            left = right;
            i++;
        }
        s.resize(right - 1);
        return s;  
    }
};


class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());

        int b = 0;
        int e = 0;
        int k = 0;
        int n = s.length();

        while(b < n)
        {
            while(b < n && s[b] == ' ') { ++b;}

            if(b == n)
                break;

            while(b < n && s[b] != ' ')
            {
                s[k++] = s[b++];
            }
            
            reverse(s.begin() + e, s.begin() + k);
            s[k++] = ' ';
            e = k;
            ++b;
        }
        s.resize(k -1);

        return s;
    }
};