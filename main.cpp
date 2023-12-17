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

class Solution {
public:
    /*!
        \brief A simple stack wrapper around a native array.
        This is a utility class for the Fibonacci algorithm.
    */
    template <typename T>
    class static_stack_t {
    public:
        template <size_t C> static_stack_t(T (&array)[C]) : static_stack_t{array, C} {}
        static_stack_t(T array[], size_t capacity) : ary_{array}, capacity_{capacity} {}

        static_stack_t& push(T const value) { assert(capacity() > size()); ary_[tos_++] = std::move(value); return *this; }
        template <typename... A> static_stack_t& push(A... args) { return push(T{args...}); }
        T pop() { assert(!empty()); return ary_[--tos_]; }
        size_t capacity() const { return capacity_; }
        size_t size() const { return tos_; }
        bool empty() const { return 0 == size(); }
        bool full() const { return capacity() == size(); }

    private:
        T* ary_; //!< Array that contains the stack.
        size_t tos_{}; //!< Top of stack index.
        size_t capacity_{}; //!< Capacity of 'ary_'.
    };

    /*
        Fibonacci iterative solution:
        
                 fib(5) = *5-00
                          /    \
                   +-----+      +----+
                  /                   \
                *4-01                  3-02
             /         \              /    \
           *3-03       *2-04         2-05   1-06
           /    \      /    \       /    \
         *2-07  *1-08 1-09   0-10  1-11   0-12
         /    \
       *1-13  *0-14

        The label format of nodes above is: fibonacci_number-I,
        where 'I' is a unique node ID used to identify each 
        individual node.

        WITH memoization (a cache of previously calculated values):

            'n' = The requested Fibonacci number, e.g. 10 in fib(10) == 55.
        
            Time = O(2n) => O(n)
            
            Because only the leftmost branch of branch of the tree is fully
            explored (iterated).  All other branch values are calculated and
            stored in the memoized values by the time they're needed - after
            the leftmost branch has been explored.  Explored (visited) nodes
            in the tree above are denoted with a '*'.  All other nodes are 
            skipped by this algorithm.

            The '2' in 'O(2n)' is because the algorithm loops once for each 
            child of each visited node (and only the leftmost nodes are visited.)
            
            This approach works because the right child of any node in the 
            Fibonacci binary tree has a tree whose size is less than or equal 
            to the size of the left child tree AND the nodes in the right child 
            tree will only contain values that have already been calculated by
            the left child tree, since the left child tree is evaluated first.
        
            Space = O(n + max(2, n + 1)) => O(2n + 1) => O(n)

            The first term [n] is for the tree node [visitation] stack.
            The second term [max(2, n + 1)] is for the memoized values.

        Unrolling the algorithm for fib(5), as shown in the tree above:
            
        result = 0
        memoized values = [0 1 0 0 0 0]
        
        push 5-00            [stack=5-00]                      [memo=0 1 0 0 0 0]

        pop 5-00             [stack=empty]                     [memo=0 1 0 0 0 0]
        push 3-02 (right)    [stack=3-02]                      [memo=0 1 0 0 0 0]
        push 4-01 (left)     [stack=4-01]                      [memo=0 1 0 0 0 0]
        
        Begin traverstal of the left side of the binary tree:
        
        pop 4-01             [stack=3-02]                      [memo=0 1 0 0 0 0]
        push 2-04 (right)    [stack=3-02 2-04]                 [memo=0 1 0 0 0 0]
        push 3-03 (left)     [stack=3-02 2-04 3-03]            [memo=0 1 0 0 0 0]
        
        pop 3-03             [stack=3-02 2-04]                 [memo=0 1 0 0 0 0]
        push 1-08 (right)    [stack=3-02 2-04 1-08]            [memo=0 1 0 0 0 0]
        push 2-07 (left)     [stack=3-02 2-04 1-08 2-07]       [memo=0 1 0 0 0 0]
        
        pop 2-07             [stack=3-02 2-04 1-08]            [memo=0 1 0 0 0 0]
        push 0-14 (right)    [stack=3-02 2-04 1-08 0-14]       [memo=0 1 0 0 0 0]
        push 1-13 (left)     [stack=3-02 2-04 1-08 0-14 1-13]  [memo=0 1 0 0 0 0]
        
        pop 1-13             [stack=3-02 2-04 1-08 0-14]       [memo=0 1 0 0 0 0]
        No new value to push because last popped value < 2.
        result += 1 = 1                                        [memo=0 1 1 0 0 0]

        pop 0-14             [stack=3-02 2-04 1-08]            [memo=0 1 1 0 0 0]
        No new value to push because last popped value < 2.
        result += 0 = 1                                        [memo=0 1 1 0 0 0]

        pop 1-08             [stack=3-02 2-04]                 [memo=0 1 1 0 0 0]
        No new value to push because last popped value < 2.
        result += 1 = 2                                        [memo=0 1 1 2 0 0]

        pop 2-04             [stack=3-02]                      [memo=0 1 1 2 0 0]
        Using preexisting memoized value for 2.
        result += 1 = 3                                        [memo=0 1 1 2 3 0]

        This completes the traversal of the left side of the binary tree.
        Begin traversal of the right side of the binary tree:

        pop 3-02             [stack=empty]                     [memo=0 1 1 2 3 0]
        Using preexisting memoized value for 3.
        result += 2 = 5                                        [memo=0 1 1 2 3 5]

        result == 5

        This completes the traversal of the right side of the binary tree.
        The stack is empty so all nodes have been visited and the algorithm is complete.
    */
    template <typename T>
    T fib(T n) const {
        T result{};

        if (1 < n) {
            auto const stack_size = n;
            struct fibnum_t {
                T val; // The value in the fibonacci tree, e.g. 4.
                T parent; // Parent value in fibonacci tree, e.g. 5 when val is 4.

                fibnum_t() = default;
                fibnum_t(T val, T parent = {}) : val{std::move(val)}, parent{std::move(parent)} {}
                operator T() const { return val; }
            };
            fibnum_t stack_array[stack_size]; // Fast allocation; no heap.
            static_stack_t<fibnum_t> stack(stack_array, stack_size);
            
            auto const memoized_values_size = (std::max)(static_cast<T>(2), n + static_cast<T>(1));
            T memoized_values[memoized_values_size]; // Cache of previously calculated fibonacci values.
            std::fill_n(memoized_values, memoized_values_size, 0);
            memoized_values[1] = 1;
            
            stack.push(n);
            while (!stack.empty()) {
                auto const fibnum = stack.pop();
                auto const memoized_value = memoized_values[fibnum];
                auto const memoized_value_exists = 0 != memoized_value;
                if (memoized_value_exists) {
                    result += memoized_value;
                    memoized_values[fibnum.parent] = result; // Update memoized value.
                } else {
                    auto const push_fibnums = 1 < fibnum;
                    if (push_fibnums) {
                        stack.push(fibnum - 2, fibnum);
                        stack.push(fibnum - 1, fibnum);
                    } else {
                        result += fibnum;
                        memoized_values[fibnum.parent] = result; // Update memoized value.
                    }
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
