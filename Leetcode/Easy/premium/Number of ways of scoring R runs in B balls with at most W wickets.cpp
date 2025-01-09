Number of ways of scoring R runs in B balls with at most W wickets

Given three integers R, B, and W which denote the number of runs, balls, and wickets. One can score 0, 1, 2, 3, 4, 6, or a wicket in a single ball in a cricket match. The task is to count the number of ways in which a team can score exactly R runs in exactly B balls with at-most W wickets. Since the number of ways will be large, print the answer modulo 1000000007. 
Examples: 



nput: R = 4, B = 2, W = 2 
Output: 7 
The 7 ways are: 
0, 4 
4, 0 
Wicket, 4 
4, Wicket 
1, 3 
3, 1 
2, 2 
Input: R = 40, B = 10, W = 4 
Output: 653263 





Approach: The problem can be solved using Dynamic Programming and Combinatorics. The recurrence will have 6 states, we initially start with runs = 0, balls = 0 and wickets = 0. The states will be: 
 

If a team scores 1 run off a ball then runs = runs + 1 and balls = balls + 1.
If a team scores 2 runs off a ball then runs = runs + 2 and balls = balls + 1.
If a team scores 3 runs off a ball then runs = runs + 3 and balls = balls + 1.
If a team scores 4 runs off a ball then runs = runs + 4 and balls = balls + 1.
If a team scores 6 runs off a ball then runs = runs + 6 and balls = balls + 1.
If a team scores no run off a ball then runs = runs and balls = balls + 1.
If a team loses 1 wicket off a ball then runs = runs and balls = balls + 1 and wickets = wickets + 1.
The DP will consist of three stages, with the run state being a maximum of 6 * Balls, since it is the maximum possible. Hence dp[i][j][k] denotes the number of ways in which i runs can be scored in exactly j balls with losing k wickets. 
Below is the implementation of the above approach: 










// C++ implementation of the approach
#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define RUNMAX 300
#define BALLMAX 50
#define WICKETMAX 10
 
// Function to return the number of ways
// to score R runs in B balls with
// at most W wickets
int CountWays(int r, int b, int l, int R, int B, int W,
              int dp[RUNMAX][BALLMAX][WICKETMAX])
{
 
    // If the wickets lost are more
    if (l > W)
        return 0;
 
    // If runs scored are more
    if (r > R)
        return 0;
 
    // If condition is met
    if (b == B && r == R)
        return 1;
 
    // If no run got scored
    if (b == B)
        return 0;
 
    // Already visited state
    if (dp[r][b][l] != -1)
        return dp[r][b][l];
 
    int ans = 0;
 
    // If scored 0 run
    ans += CountWays(r, b + 1, l, R, B, W, dp);
    ans = ans % mod;
 
    // If scored 1 run
    ans += CountWays(r + 1, b + 1, l, R, B, W, dp);
    ans = ans % mod;
 
    // If scored 2 runs
    ans += CountWays(r + 2, b + 1, l, R, B, W, dp);
    ans = ans % mod;
 
    // If scored 3 runs
    ans += CountWays(r + 3, b + 1, l, R, B, W, dp);
    ans = ans % mod;
 
    // If scored 4 runs
    ans += CountWays(r + 4, b + 1, l, R, B, W, dp);
    ans = ans % mod;
 
    // If scored 6 runs
    ans += CountWays(r + 6, b + 1, l, R, B, W, dp);
    ans = ans % mod;
 
    // If scored no run and lost a wicket
    ans += CountWays(r, b + 1, l + 1, R, B, W, dp);
    ans = ans % mod;
 
    // Memoize and return
	// we are storing possible ways when r, b, l values are present in matrix 
    return dp[r][b][l] = ans;
}
 
// Driver code
int main()
{
    int R = 40, B = 10, W = 4;
 
    int dp[RUNMAX][BALLMAX][WICKETMAX];
    memset(dp, -1, sizeof dp);
 
    cout << CountWays(0, 0, 0, R, B, W, dp);
 
    return 0;
}