Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:


 

Example 1:

Input: rowIndex = 3
Output: [1,3,3,1]
Example 2:

Input: rowIndex = 0
Output: [1]
Example 3:

Input: rowIndex = 1
Output: [1,1]
 

Constraints:

0 <= rowIndex <= 33


class Solution {
public:
    vector<int> getRow(int rowIndex) {
        
        if(rowIndex < 1)
            return {1};

        vector<int> dp(2, 1);
        
        for(int i = 2; i <= rowIndex; ++i)
        {
            dp.push_back(1);

            for(int x  = i -1; x > 0; --x)
                dp[x] = dp[x] + dp[x-1];
        }
        return dp;
    }
};