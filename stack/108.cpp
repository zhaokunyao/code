#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <climits>

using namespace std;


class MinStack {
    public:
        stack<vector<int>> sk;
        /** initialize your data structure here. */
        MinStack() {
        }

        void push(int x) {
            int min;
            if (sk.empty()) {
                min = x;
            } else {
                min = getMin();
                if (x < min) {
                    min = x;
                }
            }
            vector<int> tmp = {x, min};
            sk.push(tmp);
        }

        void pop() {
            if (sk.empty()) {
                return;
            }
            sk.pop();
        }

        int top() {
            vector<int> top = sk.top();
            return top[0];
        }

        int getMin() {
            vector<int> top = sk.top();
            return top[1];
        }
};

int main() {
    MinStack obj;
    int x   = 10;
    obj.push(x);
    obj.pop();
    int y   = 20;
    obj.push(y);
    int param_3 = obj.top();
    int param_4 = obj.getMin();
    cout << param_3 << endl;
    cout << param_4 << endl;
    return 0;
}
