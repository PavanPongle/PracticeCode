Given an integer n, return true if it is a power of two. Otherwise, return false.

An integer n is a power of two, if there exists an integer x such that n == 2x.

 

Example 1:

Input: n = 1
Output: true
Explanation: 20 = 1
Example 2:

Input: n = 16
Output: true
Explanation: 24 = 16
Example 3:

Input: n = 3
Output: false
 

Constraints:

-231 <= n <= 231 - 1
 

Follow up: Could you solve it without loops/recursion?

// we can solve using log2(N) alos, it is return the int then it is pow 

class Solution {
public:
    bool isPowerOfTwo(int n) {
        int bits = sizeof(n)*8 - 1; // we have one signed bit, ignore it
        int val = 1; // ie. position 0, power 0, 

        do {
            if (val == (n))
                return true;

            val = val << 1; // note the position of shift it is after compare

        } while (--bits); // loop should run for total bits - 1

        return false;
    }
};