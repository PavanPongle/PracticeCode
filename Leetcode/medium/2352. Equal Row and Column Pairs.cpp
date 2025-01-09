Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri and column cj are equal.

A row and column pair is considered equal if they contain the same elements in the same order (i.e., an equal array).

 

Example 1:


Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
Output: 1
Explanation: There is 1 equal row and column pair:
- (Row 2, Column 1): [2,7,7]
Example 2:


Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
Output: 3
Explanation: There are 3 equal row and column pairs:
- (Row 0, Column 0): [3,1,2,2]
- (Row 2, Column 2): [2,4,2,2]
- (Row 3, Column 2): [2,4,2,2]
 
 
// Here we have used the custom hash function for finding hash of row, 
// and then used hash of column and comapred it
// instead of that we can use the map<vector<int>, int>, it will work on comparision operation
// and we can find the requency and even compare the elements
 
class Solution {
public:
    template <class T> 
    void hash_combine(std::size_t& seed, const T& v) {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    int equalPairs(vector<vector<int>>& grid) {

        // it is frequencey count for group of integers
        // we can use the hash on group of int

        unordered_map<size_t, int> rows;
        int cnt = 0;
        size_t seed ;
		//find the hash of row and store its frequencey
        for (int i = 0; i < grid.size() ; ++i) {
            seed = grid[0].size();
            for (int y : grid[i]) {
                hash_combine<int>(seed, y);
            }
            ++rows[seed];
        }

        int nrows = grid.size();
        int ncols = grid[0].size();
		// find hash of column and compare it with hash of row and include its frequencey
        for (int i = 0; i < ncols; ++i) {
            seed = grid[0].size();
            for (int j = 0; j < nrows; ++j) {
                hash_combine<int>(seed, grid[j][i]);
            }

            if (rows.find(seed) != rows.end())
                cnt += rows[seed];
        }

        return cnt;
    }
};

class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int i,j,result = 0;
        
        int row = grid.size();
        int col = row;
        map<vector<int>, int> m;

		//storing row in map
        for(auto k:grid){
            m[k]++;
        }

		//temp vector used to store coloumn
		vector<int> vec;
        for(i=0; i<col; i++){
            for(j=0; j<row; j++){
                vec.push_back(grid[j][i]);
            }
            if(m.find(vec) != m.end()){
                result += m[vec];
            }
            vec.clear();
        }
        return result;
    }
};