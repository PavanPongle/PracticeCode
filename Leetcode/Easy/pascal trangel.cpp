Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:


 

Example 1:

Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
Example 2:

Input: numRows = 1
Output: [[1]]
 

Constraints:




class Solution {
public:

    // This can be solved using dp

    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;

        vector<int> dp;
        dp.push_back(1); // row 1, base condition
        res.push_back(dp);

        if(numRows == 1)
            return res;

        dp.push_back(1);  // row 2, base condition
        res.push_back(dp);

        //now run from row 3
        for(int i = 2 ; i < numRows ; ++i)
        {
            dp.push_back(1); // this is for end value 
            
            // The only values changed from last row
            // are all except at 0 and i, i.e first and last
            // note this reverse order of loop is imp,
            // if we take forward order of loop, it will change the value of 
            // x - 1, which is wrong, we need value from last row not from updated this row
            for(int x = i - 1; x > 0 ; --x )
            {
                dp[x] = dp[x] + dp[x -1];
            }
            res.push_back(dp);
        }

        /*
        for(int i = 0 ; i < numRows ; ++i)
        {
            vector<int> row;
            for (int j = 0 ; j <= i ; ++j)
            {
                if(j == 0 || j == i )
                    row.push_back(1);
                else
                    row.push_back(res[i-1][j-1] + res[i-1][j]);
            }
            res.push_back(row);
        }
        */
        return res;
    }
};