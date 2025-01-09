We are given an array asteroids of integers representing asteroids in a row. The indices of the asteriod in the array represent their relative position in space.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

 

Example 1:

Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
Example 2:

Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.
Example 3:

Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.
 
 
// solution is stack based
// asteroids collision only happen when
// there is positive number followed by negative number
 class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {

        vector<int> v; // kind of stack only, for storing numbers

        for (int i = 0; i < asteroids.size(); ++i) {
            
			// if curr is negative number and there exist positive number on stack
			if (!v.empty() && signbit(asteroids[i]) && !signbit(v.back())) {
				
				// if we find a negative number whose last was positive number then
                bool isDestroyed = false;
				
				// iterate until there is positve number
                while (!v.empty() && !signbit(v.back())) {
					
                    if (v.back() < abs(asteroids[i]))
                        v.pop_back(); // smaller positive gets destroy
					
                    else if (v.back() == abs(asteroids[i])) {
                        isDestroyed = true;
                        v.pop_back();
						// both gets destroy
                        break;
                    } else {
						// current gets destroy
                        isDestroyed = true;
                        break;
                    }
                }
				
                if(!isDestroyed)
                {
                    v.push_back(asteroids[i]);
                }
            } else {
				//add number add in stack, it could be positve or negative
                v.push_back(asteroids[i]);
            }
        }
        return v;
    }
};