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
    Iterative solution:
        
        Time = O(2^n), because each fibonacci number is calculated
                       from TWO previous fibonacci numbers, e.g.
                       fib(5) =
                                                   5-00
                                                  /    \
                                           +-----+      +----+
                                          /                   \
                                         4-01                  3-02
                                     /         \              /    \
                                    3-03        2-04         2-05   1-06
                                   /    \      /    \       /    \
                                  2-07   1-08 1-09   0-10  1-11   0-12
                                 /    \
                                1-13   0-14

                       Therefore the maximum possible number of 
                       nodes in the tree is 2^n-1 (2^5-1 == 31, in this case.)
                       The label format of nodes above is: fibonacci_number-n,
                       where 'n' is a unique node ID used to identify each 
                       individual node.
        
        Space = O(1), because the maximum depth of the tree is Log2(31)
                      and 31 is constant.
*/
class Solution {
public:
    /*
        Stack based algorithm:
            
        result = 0
        
        push 5-00            [stack=5-00]

        pop 5-00             [stack=empty]
        push 3-02 (right)    [stack=3-02]
        push 4-01 (left)     [stack=4-01]
        
        // Begin traverstal of the left side of the binary tree.
        
        pop 4-01             [stack=3-02]
        push 2-04 (right)    [stack=3-02 2-04]
        push 3-03 (left)     [stack=3-02 2-04 3-03]
        
        pop 3-03             [stack=3-02 2-04]
        push 1-08 (right)    [stack=3-02 2-04 1-08]
        push 2-07 (left)     [stack=3-02 2-04 1-08 2-07]
        
        pop 2-07             [stack=3-02 2-04 1-08]
        push 0-14 (right)    [stack=3-02 2-04 1-08 0-14]
        push 1-13 (left)     [stack=3-02 2-04 1-08 0-14 1-13]
        
        pop 1-13             [stack=3-02 2-04 1-08 0-14]
        // NOTE: No new value to push because last popped value < 2.
        result += 1 = 1

        pop 0-14             [stack=3-02 2-04 1-08]
        // NOTE: No new value to push because last popped value < 2.
        result += 0 = 1

        pop 1-08             [stack=3-02 2-04]
        // NOTE: No new value to push because last popped value < 2.
        result += 1 = 2

        pop 2-04             [stack=3-02]
        push 1-00 (right)    [stack=3-02 1-09]
        push 0-10 (left)     [stack=3-02 1-09 0-10]
        
        pop 0-10             [stack=3-02 1-09]
        // NOTE: No new value to push because last popped value < 2.
        result += 0 = 2

        pop 1-09             [stack=3-02]
        // NOTE: No new value to push because last popped value < 2.
        result += 1 = 3

        // This completes the traversal of the left side of the binary tree.
        // Now begin traversal of the right side of the binary tree.

        pop 3-02             [stack=empty]
        push 1-06 (right)    [stack=1-06]
        push 2-05 (left)     [stack=1-06 2-05]

        pop 2-05             [stack=1-06]
        push 0-12            [stack=1-06 0-12]
        push 1-11            [stack=1-06 0-12 1-11]

        pop 1-11             [stack=1-06 0-12]
        // NOTE: No new value to push because last popped value < 2.
        result += 1 = 4

        pop 0-12             [stack=1-06]
        // NOTE: No new value to push because last popped value < 2.
        result += 0 = 4

        pop 1-06             [stack=empty]
        result += 1 = 5

        // NOTE: result == 5.

        // This completes the traversal of the right side of the binary tree.
        // The stack is empty so all nodes have been visited and the algorithm is complete.
    */

// Helper macros for fixed size stack (built on an array).
#define push(VAL) (cout << "push(" << VAL << ")\n", assert(/*std::size(stack)*/n > tos), stack[tos++] = (VAL))
#define pop() (assert(0 < tos), cout << "pop(" << stack[tos - 1] << ")\n", stack[--tos])
#define stack_empty() (0 == tos)
#define add_to_result(VAL) (cout << result << " + " << VAL << " = " << (result + VAL) << "\n", result += (VAL))

    template <typename T>
    T fib(T n) const {
        T result{};

        if (1 < n) {
            T stack[n]; // Fast allocation; no heap.
            size_t tos{}; // Index of next available location (last element + 1).
            
            push(n);
            while (!stack_empty()) {
                auto const fibnum = pop();
                if (1 < fibnum) {
                    push(fibnum - 2);
                    push(fibnum - 1);
                } else {
                    add_to_result(fibnum);
                }
            }
        } else {
            result = n;
        }

        return result;
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
