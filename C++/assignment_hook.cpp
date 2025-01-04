// assignment_hook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <mutex>

template<typename T>
class assignment_hook {
public:
    using hook_t = std::function<void(const T& old_value, const T& new_value)>;

    assignment_hook(T& value, hook_t hook) : ref_(value), hook_(hook) {}

    operator bool() { return ref_; }

    T& operator=(const T& rhs)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ref_ = rhs;
        hook_(ref_, rhs);
        return ref_;
    }
private:
    // I'd rather not want to think about copying this
    assignment_hook(const assignment_hook&);
    void operator=(const assignment_hook&);

    T& ref_;
    hook_t hook_;
    std::mutex mutex_;
};

void ValueChanged(int a, int b)
{
    std::cout << "value changed\n" << a << b;
}

int main()
{
    std::cout << "Hello World!\n";
    int aa = 10;
    
    assignment_hook<int> a(aa, ValueChanged);

    a = 5;

    if (a)
    {
        std::cout << "true\n";
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
