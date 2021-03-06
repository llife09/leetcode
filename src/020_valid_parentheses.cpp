
/*
Valid Parentheses

URL: https://leetcode.com/problems/valid-parentheses
Tags: ['string', 'stack']
___

Given a string containing just the characters `'('`, `')'`, `'{'`, `'}'`,
`'['` and `']'`, determine if the input string is valid.

An input string is valid if:

  1. Open brackets must be closed by the same type of brackets.
  2. Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

Example 1:

    Input:  "()"
    Output: true


Example 2:

    Input:  "()[]{}"
    Output: true


Example 3:

    Input:  "(]"
    Output: false


Example 4:

    Input:  "([)]"
    Output: false


Example 5:

    Input:  "{[]}"
    Output: true
*/

#include "test.h"

using std::map;
using std::stack;
using std::string;

namespace valid_parentheses {

inline namespace v1 {
class Solution {
    struct Record {
        int id;
        int sum;
    };

public:
    bool isValid(string s) {
        static map<char, int> table = {
            {'(', 1}, {'{', 2}, {'[', 3}, {')', -1}, {'}', -2}, {']', -3},
        };
        stack<Record> st;
        for (auto c : s) {
            int v = table[c];
            if (st.empty()) {
                st.push(Record{abs(v), v});
            } else {
                if (st.top().id != abs(v)) {
                    st.push(Record{abs(v), v});
                } else {
                    st.top().sum += v;
                }
            }
            if (st.top().sum < 0) {
                return false;
            } else if (st.top().sum == 0) {
                st.pop();
            }
        }
        return st.empty();
    }
};
} // namespace v1

TEST_CASE("Valid Parentheses") {
    TEST_SOLUTION(isValid, v1) {
        CHECK(isValid("()"));
        CHECK(isValid("()[]{}"));
        CHECK_FALSE(isValid("(]"));
        CHECK_FALSE(isValid("([)]"));
        CHECK(isValid("{[]}"));

        BENCHMARK("") { return isValid("{[()]}"); };
    };
}

} // namespace valid_parentheses
