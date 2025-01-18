You are given a 0-indexed integer array nums and an integer k.

Return an integer that denotes the sum of elements in nums whose corresponding indices have exactly k set bits in their binary representation.

The set bits in an integer are the 1's present when it is written in binary.

For example, the binary representation of 21 is 10101, which has 3 set bits.
 

Example 1:

Input: nums = [5,10,1,5,2], k = 1
Output: 13
Explanation: The binary representation of the indices are: 
0 = 0002
1 = 0012
2 = 0102
3 = 0112
4 = 1002 
Indices 1, 2, and 4 have k = 1 set bits in their binary representation.
Hence, the answer is nums[1] + nums[2] + nums[4] = 13.
Example 2:

Input: nums = [4,3,2,1], k = 2
Output: 1
Explanation: The binary representation of the indices are:
0 = 002
1 = 012
2 = 102
3 = 112
Only index 3 has k = 2 set bits in its binary representation.
Hence, the answer is nums[3] = 1.

class Solution {
public:
    int sumIndicesWithKSetBits(vector<int>& nums, int k) {
                int res = 0;
        for(int i = 0; i < nums.size(); i++) {
            int c = 0, copy = i;
            while(copy) {
                c += copy & 1;
                copy >>= 1;
            }    
            if(c == k) res += nums[i];
        }
        return res;
    }
};

1. Using the built-in __builtin_popcount() function:
This is the most efficient method and is usually the best choice.

int main() {
    int num = 42;
    int count = __builtin_popcount(num);

    std::cout << "Number of set bits: " << count << std::endl;

    return 0;
}

3. Using the Brian Kernighan's Algorithm:
This method exploits the fact that n & (n - 1) clears the least significant set bit.

int main() {
    int num = 42;
    int count = 0;

    while (num) {
        num &= num - 1; 
        count++;
    }

    std::cout << "Number of set bits: " << count << std::endl;

    return 0;
}

for num = 999999

num       0000011110100001000111111
num -1    0000011110100001000111110
new num = 0000011110100001000111110

num       0000011110100001000111110
num -1    0000011110100001000111101
new num = 0000011110100001000111100

num       0000011110100001000111100
num -1    0000011110100001000111011
new num = 0000011110100001000111000

num       0000011110100001000111000
num -1    0000011110100001000110111
new num = 0000011110100001000110000

num       0000011110100001000110000
num -1    0000011110100001000101111
new num = 0000011110100001000100000

num       0000011110100001000100000
num -1    0000011110100001000011111
new num = 0000011110100001000000000

num       0000011110100001000000000
num -1    0000011110100000111111111
new num = 0000011110100000000000000

num       0000011110100000000000000
num -1    0000011110011111111111111
new num = 0000011110000000000000000

num       0000011110000000000000000
num -1    0000011101111111111111111
new num = 0000011100000000000000000

num       0000011100000000000000000
num -1    0000011011111111111111111
new num = 0000011000000000000000000

num       0000011000000000000000000
num -1    0000010111111111111111111
new num = 0000010000000000000000000

num       0000010000000000000000000
num -1    0000001111111111111111111
new num = 0000000000000000000000000


total 12 iterations, Number of set bits: 12