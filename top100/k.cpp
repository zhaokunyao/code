#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int romanToInt(string s) {
            map<char, int> hash= {
                {'I', 1},
                {'V', 5},
                {'X', 10},
                {'L', 50},
                {'C', 100},
                {'D', 500},
                {'M', 1000},
            };
            int length = s.size();
            int sum = hash[s[0]];
            for (int i=1; i<length; i++) {
                auto v = hash[s[i]];
                auto v_old = hash[s[i-1]];
                sum +=v;
                if (v_old < v) {
                    sum -= 2*v_old;
                }
            }
            return sum;
        }
};

int main() {
    Solution o;
    {
        string s = "MCMXCVI";
        cout << o.romanToInt(s) << endl;
    }
    {
        string s = "I";
        cout << o.romanToInt(s) << endl;
    }
    {
        string s = "IX";
        cout << o.romanToInt(s) << endl;
    }
    {
        string s = "VIX";
        cout << o.romanToInt(s) << endl;
    }
    return 0;
}
