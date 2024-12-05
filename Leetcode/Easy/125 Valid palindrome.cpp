A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

 

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
 

Constraints:

1 <= s.length <= 2 * 105
s consists only of printable ASCII characters.

// note;
// Alphanumeric characters include letters and numbers.
// and we can compare the upper and lower letter only when they are convered.
class Solution {
public:

    bool toLower(string& s, int i)
    {
        if(s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] += 'a' - 'A'; 
        }
        else if(s[i] >= '0' && s[i] <= '9')
        {
            return true;
        }
        else if(!(s[i] >= 'a' && s[i] <= 'z'))
        {
            return false;
        }
        return true;
    }

    bool isPalindrome(string s) {

        for (int i = 0, j = s.length() - 1; i < j;) {
            if (!toLower(s, i)) {
                ++i;
                continue;
            }

            if (!toLower(s, j)) {
                --j;
                continue;
            }

            if (s[i] != s[j])
                return false;
            else
                {++i; --j;}
        }

            return true;

    }
};


// using stl
bool isPalindrome(string s) {
        int left = 0, right = s.length()-1;
        while(left<right)
        {
            if(!isalnum(s[left])) left++;
            else if(!isalnum(s[right])) right--;
            else if(tolower(s[left])!=tolower(s[right])) return false;
            else {left++; right--;}
        }
        return true;
    }