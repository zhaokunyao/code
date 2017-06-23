#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    public:
        vector<int> plusOne(vector<int>& digits) {
            int carry = 1;
            int length = digits.size();
            vector<int> res;
            for (int i =length-1; i>=0; i--) {
                auto n = digits[i] + carry;
                if (n >= 10) {
                    carry = 1;
                    n = n - 10;
                } else {
                    carry = 0;
                }
                res.insert(res.begin(), n);
            }
            if (carry == 1) {
                res.insert(res.begin(), carry);
            }
            return res;
        }

};

int main() {
    Solution o;
    {
        vector<int> digits = {1,3,5,9};
        vector<int> res = o.plusOne(digits);
        for (auto && n : res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    {
        vector<int> digits = {9};
        vector<int> res = o.plusOne(digits);
        for (auto && n : res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    return 0;
}
