#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <map>

using namespace std;

class Solution {
    public:
        bool isValid(string s) {
            stack<char> sk;

            for (auto c : s) {
                if (c == '(' || c == '[' || c == '{') {
                    sk.push(c);
                    continue;
                }
                if (sk.empty()) {
                    return false;
                }
                if (c == ')' && sk.top() != '(') {
                    return false;
                }
                if (c == ']' && sk.top() != '[') {
                    return false;
                }
                if (c == '}' && sk.top() != '{') {
                    return false;
                }
                sk.pop();
            }

            if (sk.empty()) {
                return true;
            }

            return false;
        }
};

int main() {
    Solution * o = new Solution();
    {
        string s = "()[]{}";
        cout << o->isValid(s) << endl;
    }
    {
        string s = "([]{})";
        cout << o->isValid(s) << endl;
    }
    {
        string s = "([)]";
        cout << o->isValid(s) << endl;
    }
    return 0;
}
