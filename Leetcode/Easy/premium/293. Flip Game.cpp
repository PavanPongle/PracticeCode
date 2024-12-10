You are playing a Flip Game with your friend.

You are given a string currentState that contains only '+' and '-'. You and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move, and therefore the other person will be the winner.

Return all possible states of the string currentState after one valid move. You may return the answer in any order. If there is no valid move, return an empty list [].

 

Example 1:

Input: currentState = "++++"
Output: ["--++","+--+","++--"]
Example 2:

Input: currentState = "+"
Output: []
 

Constraints:

1 <= currentState.length <= 500
currentState[i] is either '+' or '-'.
Solutions
Solution 1: Traversal + Simulation
We traverse the string. If the current character and the next character are both +, we change these two characters to -, add the result to the result array, and then change these two characters back to +.

After the traversal ends, we return the result array.

class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> ans;
        for (int i = 0; i < s.size() - 1; ++i) {
            if (s[i] == '+' && s[i + 1] == '+') {
                s[i] = s[i + 1] = '-';
                ans.emplace_back(s);
                s[i] = s[i + 1] = '+';
            }
        }
        return ans;
    }
};