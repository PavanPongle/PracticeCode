ou are given two jugs with capacities x liters and y liters. You have an infinite water supply. Return whether the total amount of water in both jugs may reach target using the following operations:

Fill either jug completely with water.
Completely empty either jug.
Pour water from one jug into another until the receiving jug is full, or the transferring jug is empty.
 

Example 1:

Input: x = 3, y = 5, target = 4

Output: true

Explanation:

Follow these steps to reach a total of 4 liters:

Fill the 5-liter jug (0, 5).
Pour from the 5-liter jug into the 3-liter jug, leaving 2 liters (3, 2).
Empty the 3-liter jug (0, 2).
Transfer the 2 liters from the 5-liter jug to the 3-liter jug (2, 0).
Fill the 5-liter jug again (2, 5).
Pour from the 5-liter jug into the 3-liter jug until the 3-liter jug is full. This leaves 4 liters in the 5-liter jug (3, 4).
Empty the 3-liter jug. Now, you have exactly 4 liters in the 5-liter jug (0, 4).
Reference: The Die Hard example.

Example 2:

Input: x = 2, y = 6, target = 5

Output: false

Example 3:

Input: x = 1, y = 2, target = 3

Output: true

Explanation: Fill both jugs. The total amount of water in both jugs is equal to 3 now.


class Solution {
public:

    //This problem can be solved using the tree generation
    // by generating leeaf nodes of possible solution we can reach out to solution

    // such tree can be traveled using DFS and BFS

    // 1. Using DFS

    bool DFS(int x, int y, int target, int curr, unordered_set<int>& visited)
    {
        if(curr > (x+y) || curr < 0 || visited.find(curr) != visited.end())
            return false;

        if(curr == target)
            return true;

        visited.insert(curr);

        auto a = DFS(x, y, target, curr + x, visited);
        auto b = DFS(x, y, target, curr + y, visited);
        auto c = DFS(x, y, target, curr - x, visited);
        auto d = DFS(x, y, target, curr - y, visited);

        return a || b || c|| d;
    }

    bool canMeasureWater(int x, int y, int target) {
        

        if(x + y < target)
            return false;

        if(x == target || y == target)
            return true;

        // to limit recursion have visited nodes
        unordered_set<int> visited;
        int curr = 0;
        return DFS(x, y, target, curr, visited);
    }
};


// Using BFS
class Solution {
public:
   bool canMeasureWater(int x, int y, int target) {

        if (x + y < target)
            return false;

        if (x == target || y == target || x + y == target)
            return true;

        unordered_set<int> visited;
        queue<int> q;
        int max = x + y;
		//Note this is imp, incase we have multiple jugs we can use such technique
        vector<int> v = {x, -x, y, -y};

        q.push(0);
        visited.insert(0);
        int curr = 0;
        while (!q.empty()) {
            curr = q.front();
            q.pop();

            if (curr == target)
                return true;

            for (auto a : v) {
                int k = curr + a;

				// if it is not visited, and between 0 to max then add in queue
                if (k <= (x + y) && k >= 0 && visited.find(k) == visited.end()) {
                    q.push(k);
                    visited.insert(k);
                }
            }
        }

        return false;
    }
};