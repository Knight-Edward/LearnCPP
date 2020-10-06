#include <string>
/* 
 * This cpp file demostrates the evolution of C++
 * For refencce, checkout the paper:
 * << Evolving a language in and for the real world: C++ 1991-2006 >>
 * by Bjarne Stroustup
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

// this is done in compile time
// so STL is very fast
// algorithm
template<class Iter, class T>
Iter myFind(Iter first, Iter last, const T& val) {
    while(first != last && *first != val)
        ++first;
    return first;
}

// function object
template<typename T> struct Less_than {
    T value; // default is public in struct in C++
    Less_than(const T& v) : value(v) { }
    bool operator()(const T&v) const {
        return v > value;
    }
};

// my_find_if
template <typename In, typename Pred>
In my_find_if(In first, In last, Pred pred) {
    while(first != last && !pred(*first)) {
        ++first;
    }
    return first;
}

// normal function
bool larger_7(int a ) {
    return a > 7;
}

// accumulator
template<class T>
struct Accumulator {
    T value; // by defult, what is initialized value?
    int count;
    Accumulator() : value(), count(0) {}
    Accumulator(const T& v) : value(v), count(0) {}
    void operator() (const T& v) {
        cout << "compile value: " << value << endl;
        ++count;
        value+=v;
    }
};

// class Template for nicer syntax
class Lambda {};
template<class T>
Less_than<T> operator> (Lambda, const T& v) {
    // for this case, when we compare two oprands on ">",
    // the left one is a Lambda object, the right one is
    // a value of T type, it will return a Less_than function
    // object. To put is simply, it is a syntax sugar.
    return Less_than<T>(v);
}

int main() {
    vector<int> v{1,3,4,5,9,8,4,10};
    for(auto a : v) {
        cout << a << endl;
    }
    vector<string> v2{"Hello", "World", "This","is"};
    vector<int>::iterator ret = myFind(v.begin(), v.end(), 9);
    cout << "Find you: " << *ret << endl;
    auto ret2= myFind(v2.begin(), v2.end(), "Hello");
    cout << "Find you too: " << *ret2 << endl;
    
    // function object
    Less_than<double> f(8);  // f holds 8, f is a instantiated object whose value is 8; 
    bool b1 = f(3); // f is a function object
    bool b2 = f(4);
    cout << "b1 b2 " << b1 << " " << b2 << endl;
    // pass function object into a algorithm
    // find first iter in v whose value is larger than 8
    auto larger_than_8 = find_if(v.begin(), v.end(), f);
    cout << *larger_than_8 << endl; 
    Less_than<double> g(4);  // f holds 8, f is a instantiated object whose value is 8; 
    auto larger_than_4 = my_find_if(v.begin(), v.end(), g);
    cout << *larger_than_4 << endl; 
    // we can also pass a real function into my_find_if
    auto larger_than_7 = my_find_if(v.begin(), v.end(), larger_7);
    cout << *larger_than_7 << endl; 

    // accumulator
    vector<double> v_d;
    double d;
    while(cin>>d) v_d.push_back(d);

    Accumulator<double> ad;
    ad = for_each(v_d.begin(), v_d.end(), ad);
    cout << "Sum == " << ad.value
         << ", mean == " << ad.value / ad.count
         << "\n";

    // nicer syntax for function object
    // vector<int> v{1,3,4,5,9,8,4,10};
    Lambda X;
    vector<int>::iterator p = find_if(v.begin(), v.end(), X > 8);
    cout << "*p is : " << *p << endl;

    return 0;
}

