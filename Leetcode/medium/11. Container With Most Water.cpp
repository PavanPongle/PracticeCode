You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

 

Example 1:


Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1

class Solution {
public:

// idea is find the next max vertical length from both end 
// calculate the area, and choose if max
// here, we are keeping one pointer fixed who is current min height and advancing at other end to find greater than currnt min
    int maxArea(vector<int>& height) {
        int area = INT_MIN;

        int i = 0, j = height.size() -1 ;
        while( i < j)
        {
            int h = min(height[i], height[j]);
            area = max(area, (j - i) * h);
            while(height[i] <= h && i < j) ++i; // find next max height greater than current min height
            while(height[j] <= h && i < j) --j; // find next max height greater than current min height
        }

        return area;
    }
};