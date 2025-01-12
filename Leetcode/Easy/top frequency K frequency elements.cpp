/*
Problem: Top K Frequent Elements
 
Task: Write a function to return the k most frequent elements in an array using a min-heap.
 
Input Example: Array [1, 1, 1, 2, 2, 3], k=2
Outout Example : [1,2]
*/


struct compare
{
    bool operator ()(std::pair<int, int> a, std::pair<int, int> b) const
    {
        if(a.second == b.second)
            return a.first < b.first;
        else
            return a.second < b.second;
    }
};

std::set<int> findKMax(std::vector<int> v, int k)
{
    
    std::unordered_map<int, int> mm;
    mm.reserve(k);
    std::set<int> res;

    for(auto x : v)
    {
        mm[x]++;
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> pq(mm.begin(), mm.end());;
    
    
    for(int i = 0; i < k ; ++i)
    {
        res.insert(pq.top().first);
        pq.pop();
    }
    
    return res;
    
}

int main()
{
    auto res =findKMax({1, 1, 1, 2, 2, 3}, 2);
    
    for(auto a : res)
        std::cout << a << '\n';

    return 0;
}