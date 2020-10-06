# Tile
Evolving a language in and for the real world: C++ 1991-2006
Bjarne Stroustrup

Reading notes by Edward Wang
Date: 2020/10/02

# ch0
[Abstract]
The emphasis is on the ideals, constraints, programming techniques,
and people that shaped the language. Among the major themes are 
the emergence of generic programming ang the STL. Specific topics
include seperate compilation of templates, exception handling, and 
support for embedded systems programming.
```c++
    #include <iostream>
    using namespace std;
    int main() {
        cout << "Hello World\n";
        return 0;
    }
```
-------------------------------------------------------------

# ch1
[Introduction]
The key efforts over the initial decade after the creation of C++
are as follows:
1. use the language
2. provide better compilers, tools and libraries  
3. keep the language from fragmenting into dialects
4. keep the language and its community from stagnating




-------------------------------------------------------------
# ch2
## [background]

Two very unique design criterias(ideals):
1. There is a direct mappling of C++ language constructs to hardware.
2. The standard library is specified and implemented in C++

Most languages that provide abstraction mechanisms still have to
provide the most usefull data structures, such as strings, lists,
trees, associative arrays, vectors, matrices, and sets, as built-in
facilities, relying on other languages(such as assember, C and C++
) for their implementation. Of major languages, only C++ provides
general, flexible, exntensible, and efficient containers implemented
in the language itself.

## The birth of C with Classes
The work on what eventually became C++ started with a attempt to 
analyze the UNIX kernel to determine to what extend it could be 
distributed over a network of computers connected by a local area
network.

## Feature Overview
The earliest features included classes, derived classes, public/private
access control, type checking and implicit conversion of function 
arguements, and the overloading of the assignment operator added based
in perveived need.

In the beginning, a pre-processor was designed to translate C++ into 
C, and then the C compiler would produce the execuatable program. In
particular, having C as a subset dramatically reduced the support and 
documentation work needed. C with Classes was still seen as a dialect 
of C.

## Work Environment
There was a cultural bias against "grant projects" requireing many 
people, against "grant plans" like untested paper designs for others
to implement, and against a class distinction between desingers and 
implementers. In Computing Science Research Center it was almost a 
requirement that you - if you were not into theory - personally implemented
something embodying your ideas and found users who could benefit from
what you built.

## From C with Classed to C++
During 1982, it became clear that C with Classed was a "medium success"
and would remains so until it died.[Just like CM] As a result of the 
careful analysis, Bjarne Stroustrup began designing a cleaned-up and
extended successor to C with Classes and implementing it using traditional
compiler technology. In the move from C with Classes to C++, the type chekcing
was generally improved in ways that are possible only using a proper compiler
front-end with full understaing of all syntax and semantics. In addition,
virtual funcitons, function name and operator overloading, references, 
constants(const), and many minor facilitices were added. To many , the 
virtual functions were the major addition, as they enable object-oriented
programming.

# ch3: The C++ World in 1991

## The ISO C++ Standard Process

## ...

# ch4: The Standard Library: 1991-1998
## Basic STL Container + Iterator + Algorithm
After 1991, most major changes to the draft C++ standard were in the standard
library.

When considering designing something generic, STL is really special. Basically
it seperates three major parts, which are containers, iterators and algorithms.
This design model really shapes STL in a unique way compared with other generic 
programming languages.

For find() algorithm, a possible implementation is:
```c++
tmeplate<class Iter, class T>
Iter find(Iter first, Iter last, const T& val) {
    while(first != last && *first != val)
        ++first;
    return first;        
}
```

Let's see the implementation of list<string>::iterator:
list<string>::iterator isn't going to be a string * .In fact, assuming the most 
common implementation of a linked list, list<string>::iterator is going to be a 
Link<string> * where Link is link node type, such as:
```c++
template<class T> struct Link {
    T value;
    Link* suc;
    Link* pre;
};
```
That implies that * means p->value (return the value field), ++ means p->suc (
return a pointer to the next link), and != pointer comparison (comparing Link * )

A combination of templates and overload resolution was used to pick radically different
, yet optimal implementations of operations used in the definition of find() for each 
use of find(). Note there is no run-time dispatch, no virtual function calls. In fact,
there are only calls of trvially inlined functions and fundamental operations, such 
as * and ++ for a pointer. In terms of execution time and code size, we have hit the 
absolute minimum.

The key to both the elegance and the performance of the STL is that it is based directly
on the hardware model of memory and computation. The STL notion of a sequence is basically 
that of the hardware's view of memory as a set of sequences of objects. The basic semantics
of the STL map directly into hardware instructions allowing algorithms to be implemented 
optimally. The compile-time resolution of templates and the perfect inlining they support
is then key to the efficient mapping of the high-level expression using the STL to the hardware
level.

## Function Objects
The STL and generic programming in general owns a freely and often acknowleged debt to 
functional programming. So where are the lambdas and higher-order functions? C++ does not 
support anything like that(though there are always proposals for nested functions, closures,
lambdas, etc). Instead, classes that define the application operator, called function objects,
(or even "functors"), take the role and have become the main mechanism of parameterizaion in
modern C++ mechanisms to provide unprecedented felxitbility and performance.

```c++
// function object
template<typename T> struct Less_than {
    T value; // default is public in struct in C++
    Less_than(const T& v) : value(v) { }
    bool operator()(const T&v) const {
        return v > value;
    }
};
```

To my understanding, a function object is a template class with overloading operator ().
By doing this, we can let the instantiated class, which is called function object, play
the role of a function, which is to say, this object, can take parameters and do some sort
of calculation and return. Why is this better than a function? Function object can be initialized
with one or more arguements and carry the information along for later use. A function 
object can carry a state. That makes for more general and more elegant code.

```c++
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

int main() {
    ...
    // accumulator
    vector<double> v_d;
    double d;
    while(cin>>d) v_d.push_back(d);

    Accumulator<double> ad;
    ad = for_each(v_d.begin(), v_d.end(), ad);
    cout << "Sum == " << ad.value
         << ", mean == " << ad.value / ad.count
         << "\n";

}

```
Basically, a function object can carry a state which will be further used, which
makes it a more powerful tool than a noraml function.

## Traits [A SET OF TYPES]
C++ does not offer a general compile-time way of asking for properties of a type. In the
STL, and in many other libraries using templates to provide generic type-safe facilities
for diverse types, this became a problem. The basic solution was diccovered by Nathan Myers
during the effort to templatize iostream and string. The basic idea is to provide an 
auxiliary template, "a trait", to contain the desired information about a set of types.
Considering how to find the type of the elements pointed to by an iterator. For a 
list_iterator<T> it is list_iterator<T>::value_type and for a ordinary pointer T * it is T.
We can express that like this:
```c++
    template<class Iter>
    struct iterator_trait {
        typedef Iter::value_type value_type;
    }

    template<class T>
    struct iterator_trait<T*> {
        typedef T value_type;
    }
```
That is, the value_type of an iterator is its member type value_type. However, pointers are a common
form or iterators and they don't have any member types. So, for pointers we use the type pointed to 
as value_type. The language involved is called partial specialization.

## Iterator categories

- input iterator (ideal for homogeneous stream input)
- output iterator (ideal for homogeneous stream output)
- forward iterator (we can read and write an element repeatedly, ideal for singly-linked lists)
- bidirectional iterator (ideal for doubly-linked lists)
- random access iterator (ideal for vectors and arrays)

This classification acts as a guide to programmers who care about interoperability of algorithms
and containers. It allows us to minimize the coupling of algorithms and containers. Where different
algorithms exist for different iterator categories, and the most suitable aogorithm is automatically
chosen through overloading(compile time).

## Stepanov's view

STL is only a limited success. While it became a widely used library, its central intuition did
not get across. People confuse generic programming with using (and abusing) C++ templates. Generic 
programming is about abstracting and classifying algorithms and data structures. It gets its 
inspirations from Knuth and not from type theory. Its goal is the incremental construction of
systematic catalogs of useful, efficient and abstract algorithms and data structures. Such a 
undertaking is still a dream.


## The impact of the STL
The impact of the STL on the thinking on C++ has been immense. Before the STL, I consistently listed
three fundamental programming styles (paradigms) as being supported 
- Procedural programming
- Data abstraction
- Object-oriented programming
I saw tempaltes as support for data abstraction. After playing with the STL for a while, I factored
out a fourth style:
- Generic programming.

## Other Parts of the Standard Library

- basic language run-time support (memory management, run-time type information(RTTI), exception,etc)
- the C standard library
- the STL (containers, algorithms, iterators, function objects)
- iostreams (templatized on character type and implicitly on locale)
- locales (objects characterizing cultural preferences in I/O)
- string (templatized on character type)
- bitset (a set of bits with logical operations)
- complex (templatized on scalar type)
- valarray (templatized on scalar type)
- auto_ptr (a resource handle for objects templatized on type)

# Language Features

## Namespaces

## Run-time type information

```c++
class dialog_box : public window {
    // library class known to the "system"
 public:
    virtual int ask();
    // ...
};

class Sbox : public dialog_box {
    // can be used to communicate a string
public:
    int ask();
    virtual char* get_string();
    // ...
}

```
So, when the system/library hands me a pointer to a dialog_box, how can I know whther
it is one of my Sboxs? This question can be asked directly using the dynamic_cast operator.
```c++
void my_fct(dialog_box* bp) {
    if (Sbox* sbp = dynamic_cast<Sbox*>(bp)) {
        // use sbp
    } else {
        // treat *pb as a plain dialog box
    }
}
```
The dynamic_cast<T*>(p) converts p to the desired type T * if * p is a T or class derived
from T. Otherwise, the value of dynamic_cast<T *>(p) is 0.

## Declarations in conditions

```c++
    if (Sbox* sbp = dynamic_cast<Sbox*>(bp)) {
        // use sbp
    }
```

## The Export Controversy

## Exception Safety

## Resource Managements
Exceptions are typically - and correctly - seen as a control structure : a throw transfers
control to some catch cluase. However, sequencing of operations is only a part of the picture.
Error handing using exceptions is mostly about resource management and invariants, This view
is actually built into the C++ class and exception primitives in a way that provides a necessary
foudation for the guarantees and the standard library design. When an exception is thrown, evey
constructed object in the path from throw to the catch is destroyed. The destructors for partially
constructed objects (and unconstructed objects) are not invoked.






























