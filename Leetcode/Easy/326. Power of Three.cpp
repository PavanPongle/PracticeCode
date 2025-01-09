Given an integer n, return true if it is a power of three. Otherwise, return false.

An integer n is a power of three, if there exists an integer x such that n == 3x.

 

Example 1:

Input: n = 27
Output: true
Explanation: 27 = 33
Example 2:

Input: n = 0
Output: false
Explanation: There is no x where 3x = 0.
Example 3:

Input: n = -1
Output: false
Explanation: There is no x where 3x = (-1).
 
 class Solution {
public:
    bool isPowerOfThree(int n) {
        long long res = 1;
        while(n > res)
        {
            res *= 3;
        }
        return n == res;
    }

    /*
    if(n<=0)
         return false; //if value of n is negative or 0 it is definitely not power of 3 
     double x = log10(n)/log10(3);
     if(x==(int)x)
         return true;
     return false
	*/
};