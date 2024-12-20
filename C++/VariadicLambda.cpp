
template<typename ...T> struct overload_set;

//Base condition
template<typename T1>
struct overload_set<T1> : public T1
{
    overload_set(T1&& t1) : T1(std::move(t1)) {}
    using T1::operator();
};

//Unpacking one parameter
template<typename T1, typename ...T>
struct overload_set<T1, T ...> : public T1, public overload_set<T ...>
{
    //Note the use of std::forward syntax
    overload_set(T1&& t1, T&& ...t2) : T1(std::move(t1)), overload_set<T ...>(forward<T>(t2) ...) {}
    using T1::operator(); // expansion of current parameter
    using overload_set<T...>::operator(); // expansion of remaining packs
};

template <typename ... F>
auto overload(F&& ... f) {
    return overload_set<F ...>(std::forward<F>(f) ...);
}

/*********************************************************/

template<typename ... F>
struct overload_set2 : public F ... // note syntax, F... and not overload_set2<F...>
{
    overload_set2(F&& ...t) : F(forward<F>(t)) ... {}
    using F::operator() ...;
};

template<typename ...F>
auto overload2(F&& ...t)
{
    return overload_set2<F ...>(std::forward<F>(t) ...);
}

/*********************************************************/

template <typename ... F>
struct overload3 : public F ... {
    using F::operator() ...;
};

template <typename ... F> // Deduction guide
overload3(F&& ...) -> overload3<F ...>;

int main()
{
    int i = 2;
    double j = 1.1;
    char k = 'x';

    auto x = overload2(
        [](int i) { cout << (i); },
        [](double i) { cout << (i); },
        [](char i) { cout << (i); }
    );

    x(i);
    x(j);
    x(k);
}