#include <iostream>
#include <set>
#include <algorithm>
#include <array>

void Helper(auto it, auto& numbers, auto str)
{
    if (it == numbers.end()) {
        std::cout << str << " bound is end" << std::endl;
    } 
    else if (it == numbers.begin()) {
        std::cout <<  str << " bound is begin" << std::endl;
    }
    else
    {
        std::cout <<  str << " bound is " << *it << std::endl;
    }
}

int main() {
    std::set<int> numbers = {1, 3, 5, 7, 9};
    std::array<int, 6> targets = {-10, 1, 2, 3, 9, 12};

    for(auto target : targets)
    {
        std::cout << '\n' << "for value " << target << '\n';
        auto ite = std::equal_range(numbers.begin(), numbers.end(), target);
        auto itl = std::lower_bound(numbers.begin(), numbers.end(), target);
        auto itu = std::upper_bound(numbers.begin(), numbers.end(), target);
    
        Helper(ite.first, numbers, "equal_range lower");
        Helper(ite.second, numbers, "equal_range upper");
        Helper(itl, numbers, "lower");
        Helper(itu, numbers, "upper");

    }
    return 0;
}

{1, 3, 5, 7, 9}

for value -10
equal_range lower bound is begin
equal_range upper bound is begin
lower bound is begin
upper bound is begin

for value 0
equal_range lower bound is begin
equal_range upper bound is begin
lower bound is begin
upper bound is begin

for value 1
equal_range lower bound is begin
equal_range upper bound is 3
lower bound is begin
upper bound is 3

for value 2
equal_range lower bound is 3
equal_range upper bound is 3
lower bound is 3
upper bound is 3

for value 3
equal_range lower bound is 3
equal_range upper bound is 5
lower bound is 3
upper bound is 5

for value 9
equal_range lower bound is 9
equal_range upper bound is end
lower bound is 9
upper bound is end

for value 12
equal_range lower bound is end
equal_range upper bound is end
lower bound is end
upper bound is end