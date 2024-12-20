Given an array of integers arr, return true if the number of occurrences of each value in the array is unique or false otherwise.

 

Example 1:

Input: arr = [1,2,2,1,1,3]
Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
Example 2:

Input: arr = [1,2]
Output: false
Example 3:

Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
Output: true

//as we have constraint of 1000 elements so we used this method
// else we could have used the unordered_map for counting frequencies and set to finding uniqueness of freq
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        vector<short> freq(2001, 0);
        vector<short> cnt_of_freq(1001, 0);
        for(int i = 0 ; i < arr.size() ;  ++i)
        {
            ++freq[arr[i] + 1000 /* constraint -1000 to 1000*/];
        }

        for(auto x : freq)
        {
            if (x == 0)
                continue;
            if(cnt_of_freq[x] != 0)
                return false;
            else
                ++cnt_of_freq[x];
        }

        return true;
    }
};

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
     int n=arr.size();
     unordered_map<int,int>m;
     for(int i=0;i<n;i++){
        m[arr[i]]++;
     } 
     unordered_set<int>s;
     for(auto x:m){
        int freq=x.second;
        if(s.find(freq)!=s.end()){
            return false;
        }
        else{
            s.insert(freq);
        }
        
     }  
     return true;
    }
};