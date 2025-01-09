You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

 

Example 1:

Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:

Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
 

Constraints:

1 <= n <= 45

// Note this problem can be solved usign by generating a tree and traversing it 

class Solution {
public:
    int climbStairs(int n) {
        if(n<=1)
            return 1;

        // lets solve using dynamic programming
        // where we need solution for ith step then we have to know the 
        // solution for i-1 and i-2 steps( as we have steps 1 and 2)
        // if we have steps like 1,2,3 then i = (i -1) + (i -2) + (i-3) etc.

        vector<int> steps = {1, 2}; // this is for generalisation, we can do {1,2,3} if 3 steps

        int count = 0;
        vector<int> dp(n+1, 0);
        dp[0] = 1; // The base cases (0 and 1 steps) are initialized to 1 since there is only one way to reach them.
        dp[1] = 1; // when 1 steps has to climb, [1]
        dp[2] = 2; // when 2 steps has to climb, [1,1], [2]

        for(int i = steps.size() ; i <= n; ++i)
        {
            count = 0;
            for( auto s : steps)
            {
                if(i-s >= 0)
                    count += dp[i - s];
            }
            dp[i] = count;
        }

        return dp[n];
    }
};

