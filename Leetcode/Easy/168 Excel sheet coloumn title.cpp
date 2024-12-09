Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...
 

Example 1:

Input: columnNumber = 1
Output: "A"
Example 2:

Input: columnNumber = 28
Output: "AB"
Example 3:

Input: columnNumber = 701
Output: "ZY"
 

Constraints:

1 <= columnNumber <= 231 - 1




class Solution {
public:
    string convertToTitle(int columnNumber) {
        string s;

        int rem ;
        int q;
        
        while(columnNumber)
        {
            rem = (--columnNumber) % 26;
            columnNumber /= 26;
            //Note we are not appending it, we are inserting it at the begining
            s.insert(s.begin(), 'A' + rem );
        }

        return s;
    }
};


Intuition
This problem requires a number system conversion.
We need to convert the base(10) input to base(26).
But there's a catch. Excel system has range: [1, 26], whereas base(26) has range: [0, 25].
Approach
If we try to represent columnNumber using base(26), then they can be represented like this:
// target: AXY
columnNumber = (26^2)*(A) + (26^1)*(X) + (26^0)*(Y)
base(26)
A -> 0
B -> 1
C -> 2
and so on till, Z -> 25
But according to Excel:
A -> 1
B -> 2
C -> 3
and so on till, Z -> 26
If we observe the pattern here, numeric representation of every corresponding alphabet in Excel is one more than that of base(26), right?
So, any columnNumber can be represented using Excel format like this:
// target: AXY
columnNumber: (26^2)*(A+1) + (26^1)*(X+1) + (26^0)*(Y+1)
Why +1? Because, as explained above, each corresponding letter is one more than its corresponding representation in base(26).
Now, how do we retrieve the letters?

columnNumber = (26^2)*(A+1) + (26^1)*(X+1) + (26^0)*(Y+1)  
// to retrieve Y
    // 26^0 is just 1, so there is (1)*(Y+1)
    // to retrieve Y, subtract 1 from both side, then divide both side by 26, the remainder will be Y

// Subtracting 1 from both sides
columnNumber-1 = (26^2)*(A+1) + (26^1)*(X+1) + Y

// dividing both sides by 26
columnNumber-1 = (26^1)*(A+1) + (26^0)*(X+1)
rem = Y

// If you observe, we have just reduced our problem size, we have to conti