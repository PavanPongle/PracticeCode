There is a biker going on a road trip. The road trip consists of n + 1 points at different altitudes. The biker starts his trip on point 0 with altitude equal 0.

You are given an integer array gain of length n where gain[i] is the net gain in altitude between points i​​​​​​ and i + 1 for all (0 <= i < n). Return the highest altitude of a point.

 

Example 1:

Input: gain = [-5,1,5,0,-7]
Output: 1
Explanation: The altitudes are [0,-5,-4,1,1,-6]. The highest is 1.
Example 2:

Input: gain = [-4,-3,-2,-1,4,3,2]
Output: 0
Explanation: The altitudes are [0,-4,-7,-9,-10,-6,-3,-1]. The highest is 0.
 
 
class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        
        if(gain.size() == 1)
            return max(0, gain[0]);

		// default gain will be 0 or gain at postition 0, as we are running loop from index 1
        int max_a  = gain[0] > 0 ? gain[0] : 0;
        for(int i = 1 ; i< gain.size() ; ++i)
        {
            gain[i] += gain[i -1];
            max_a = max(max_a, gain[i]);
        }
        return max_a;
    }
};


    int largestAltitude(vector<int>& gain) {
        int maxAltitude = 0;
        int currentAltitude = 0;
        
        for (int i = 0; i < gain.size(); i++) {
            currentAltitude += gain[i];
            maxAltitude = max(maxAltitude, currentAltitude);
        }
        
        return maxAltitude;
    }