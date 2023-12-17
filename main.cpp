/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/fibonacci-number/

    NOTE: Power series (in math) describes why n/2 is 1/2 of 2^n.
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <algorithm>
#include <cassert>
#include <doctest/doctest.h> //!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
#include <iomanip>

using namespace std;

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

/*!
    f(0) = 0
    f(1) = 1
    f(n) = f(n-1) + f(n-2)
    Each value can be calculated in ascending order provided 
    that the previous two values have already been calculated:

    f(0) = 0 (fib_minus_two)
    f(1) = 1 (fib_minus_one)
              fib_minus_one       fib_minus_two    result
    f(2) = (f(2-1=1)=f(1)=1) + (f(2-2=0)=f(0)=0) = 1
         = fib_minus_one     + fib_minus_two
    f(3) = (f(3-1=2)=f(2)=1) + (f(3-2=1)=f(1)=1) = 2
    f(4) = (f(4-1=3)=f(3)=2) + (f(4-2=2)=f(2)=1) = 3
    f(5) = (f(5-1=4)=f(4)=3) + (f(5-2=3)=f(3)=2) = 5
    ...

    Time = O(n - 2) => O(n)

    Space = O(1)
*/
class Solution {
public:
    template <typename T>
    constexpr T fib(T n) {
        if (1 < n) {
            T fib_minus_one = 1, fib_minus_two = 0, result = 1; // Start with result of fib(2).
            --n;
            --n;
            while (0 < n--) {
                fib_minus_two = fib_minus_one;
                fib_minus_one = result;
                result = fib_minus_one + fib_minus_two;
            }
            
            return result;
        }

        return n;
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

TEST_CASE("Case 0")
{
    CHECK(0 == Solution{}.fib(0));
    cout << '\n';
}

TEST_CASE("Case 1")
{
    CHECK(1 == Solution{}.fib(1));
    cout << '\n';
}

TEST_CASE("Case 2")
{
    CHECK(1 == Solution{}.fib(2));
    cout << '\n';
}

TEST_CASE("Case 3")
{
    CHECK(2 == Solution{}.fib(3));
    cout << '\n';
}

TEST_CASE("Case 4")
{
    CHECK(3 == Solution{}.fib(4));
    cout << '\n';
}

TEST_CASE("Case 5")
{
    CHECK(5 == Solution{}.fib(5));
    cout << '\n';
}

TEST_CASE("Case 10")
{
    CHECK(55 == Solution{}.fib(10));
    cout << '\n';
}

TEST_CASE("Case 50")
{
    CHECK(12586269025ll == Solution{}.fib(50ll));
    cout << '\n';
}

TEST_CASE("Case 75")
{
    CHECK(2111485077978050ll == Solution{}.fib(75ll));
    cout << '\n';
}

/*
    End of "main.cpp"
*/
