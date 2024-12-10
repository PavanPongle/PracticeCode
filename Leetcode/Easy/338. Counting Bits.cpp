Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.

 

Example 1:

Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10
Example 2:

Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
 
 
 
Create a vector dp of size n + 1 to store the count of set bits for each number from 0 to n. Initialize all elements of dp to 0.

Use a loop to iterate from 0 to n (inclusive) to calculate the count of set bits for each number.

Inside the loop, check whether the current number i is even or odd by using the modulo operator (i % 2).

If i is even (i.e., i % 2 == 0), then the count of set bits for i is the same as the count of set bits for i / 2. This is because when you shift an even number right by one bit, you don't introduce any new set bits.

If i is odd (i.e., i % 2 != 0), then the count of set bits for i is one more than the count of set bits for i / 2. This is because when you shift an odd number right by one bit, you remove one set bit, and you add one more set bit if the least significant bit of i is 1.

Finally, return the dp vector, which contains the count of set bits for all numbers from 0 to n.

This approach is efficient because it avoids redundant calculations and utilizes the fact that the count of set bits in an even number is related to the count of set bits in its halved value. It has a time complexity of O(n) since it iterates through the numbers from 0 to n exactly once.


[0,1,1,2,1,2,2,3,1,2,2, 3]
 0 1 2 3 4 5 6 7 8 9 10 11

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int>dp(n+1,0);
        for(int i = 0 ; i<=n;i++)
        {
            if(i%2==0)
            {
                dp[i]=dp[i/2];
            }
            else
            {
                dp[i]=dp[i/2]+1;
            }
        }
        return dp;
    }
};