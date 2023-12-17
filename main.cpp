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

//#include <array>
#include <cassert>
#include <doctest/doctest.h> //!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
#include <iomanip>

using namespace std;

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

/*
    Recursive solution:
        
        Time = O(2^n), because each fibonacci number is calculated
                       from TWO previous fibonacci numbers, e.g.
                       fib(4) =
                                       4
                                     /   \
                                    3     2
                                   / \   / \
                                  2   1 1   0
                                 / \
                                1   0
                       Therefore the maximum possible number of 
                       calculations is 2^n-1 (2^4-1 == 15, in this case.)
                       Note that there will always be fewer because the 
                       0 and 1 base cases do not need to be calculated
                       and cause the binary tree to be "imperfect".
        
        Space = Log2(n), which is the maximum depth of the tree and 
                         therefore the maximum number of recursive calls
                         that will be made.
*/
class Solution {
public:
    template <typename T>
    constexpr T fib(T n) {
        return 1 < n ? fib(n - 1) + fib(n - 2) : n;
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

/*
    End of "main.cpp"
*/
