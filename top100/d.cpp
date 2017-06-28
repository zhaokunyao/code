#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        vector<string> fizzBuzz(int n) {
            vector<string> res;
            for (int i =1 ;i<=n ;i++) {
                if (i % 15 == 0) {
                    res.push_back("FizzBuzz");
                    continue;
                }
                if (i % 3 == 0) {
                    res.push_back("Fizz");
                    continue;
                }
                if (i % 5 == 0) {
                    res.push_back("Buzz");
                    continue;
                }
                res.push_back(to_string(i));
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<string> res = o.fizzBuzz(15);
        for (auto s: res) {
            cout << s << ", ";
        }
        cout << endl;
    }
    return 0;
}
