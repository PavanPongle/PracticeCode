
You are given a string s consisting only of lowercase English letters.

In one move, you can select any two adjacent characters of s and swap them.

Return the minimum number of moves needed to make s a palindrome.

Note that the input will be generated such that s can always be converted to a palindrome.

 
Example 1:

Input: s = "aabb"

Output: 2

Explanation:

We can obtain two palindromes from s, "abba" and "baab".

- We can obtain "abba" from s in 2 moves: "aabb" -> "abab" -> "abba".

- We can obtain "baab" from s in 2 moves: "aabb" -> "abab" -> "baab".

Thus, the minimum number of moves needed to make s a palindrome is 2.

 
Constraints:

1 <= s.length <= 2000
s consists only of lowercase English letters.
s can be converted to a palindrome using a finite number of moves.



Note:
we have to just find the steps not have to make string palindrome
1. 
When do you say that the string is Palindrome?
When it reads same forward and backward right.
This is what we will try to do in this approach.

We will go with same approach.

	We will go with first half of the elements and see if their corresponding character from last is equal, If it is equal then we move on to next character.
	If it is not we will find the pos of the nearest character from right which is same as given character.
		1. Now there are two subcases:
			a. If that position is equal to the idx itself, This means we are at odd index, Reason is since we are given a palindrome is always possible, So if this would not have been the case we would have found the position in right. In this case we will just swap it with the next element and increase the counter. For the sake of understanding, Take example of "abb" we will make it "bab" with 1 swap.
			b. If it is not then we have to swap each consecutive element from the position we found from the right, To make characters equal at that particular position.
			
int minMovesToMakePalindrome(string s) {
        int l,r,n,cnt=0;
        n=s.length();
        l=0;
        r=n-1;
        
        while(l<r){
			// if char in begin and last matches then do nothing
            if(s[l] == s[r]){
                l++;
                r--;
                continue;
            }
            
			// Now, try to find matching char in right side of current char position
			// unit such char found or we meed left end
            int idx=r;
            while(idx > l && s[idx] != s[l])
                idx--;
            
			// if we reach other end then we were at odd char ie. left one
            if(idx == l){
                // This means odd case, Just swap it with next adj char and do not need to go further
				// we are trying to move such odd element at center position
                swap(s[idx], s[idx+1]);
                cnt++;
                continue;
            }
            
			// swap until the mached char reaches the it's position in forward direction
            while(idx < r){
                swap(s[idx],s[idx+1]);
                cnt++;
                idx++;
            }
            l++;
            r--;
        }
        return cnt;
    }
	
2. another approach
where we will just try to count the number of swaps , and don;t want to form palindrome string
we will start looking from back 
	
class Solution {
public:
    int minMovesToMakePalindrome(string s) {
        int res = 0;
        while (!s.empty()) {
		
            int i = s.find(s.back()); // find from begin
			
            if (i == s.length() - 1) {
                // The character is in the middle of the palindrome
				// to move any element in center we have to do n/2 swaps
                res += i / 2;
            } else {
                // Swap the character to the correct position
                res += i;
                s.erase(i, 1); // Remove the matched character
            }
            s.pop_back(); // Remove the last character
        }
        return res;
    }
};