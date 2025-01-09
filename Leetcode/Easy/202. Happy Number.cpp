Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:

Starting with any positive integer, replace the number by the sum of the squares of its digits.
Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

 

Example 1:

Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
Example 2:

Input: n = 2
Output: false
 

Constraints:

1 <= n <= 231 - 1
Seen this question in a real interview before?
1/5


// Note termination condition is repetation of numbers

class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> mset; // to track occurance of sum
        
        while (true) {
            uint32_t digits = 0;
            int m = n;
            while (m) {
                int d = m % 10;
                m /= 10;
                digits += d * d;
            }
            n = digits;
            if (n == 1)
                return true;
            else 
                if(mset.find(digits) != mset.end()) // sum is occured already, hence exit, it is not going to be 1
                    return false;
                else
                    mset.insert(digits);
        }

        return n == 1 ? true : false;
    }
};


/***************************************** Approach 2 *****************************************/
// as it is cycle of repetation of number it can be solved using 2 pointer methods
//Solved using Floyd's Cycle-Finding Algorithm.

class Solution {
private:
    int nextNumber(int n){
        int newNumber = 0;
        while(n!=0){
            int num = n%10;
            newNumber += num*num;
            n = n/10;
        }
        return newNumber;
    }
public:
    bool isHappy(int n) {
        int slowPointer = n;
        int fastPointer = nextNumber(n);
        while(fastPointer != 1 && fastPointer != slowPointer){
            slowPointer = nextNumber(slowPointer);
            fastPointer = nextNumber(nextNumber(fastPointer));
        }
        return fastPointer==1;
    }
};

