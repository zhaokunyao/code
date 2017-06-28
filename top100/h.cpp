#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;



class Solution {
    public:
        int titleToNumber(string s) {
            int sum = 0;
            for (auto &&c :s) {
                auto tmp = c - 'A' + 1;
                sum = sum * 26 + tmp;
            }

            return sum;
        }
};

int main() {
    Solution o;
    {
        string s = "A";
        cout << o.titleToNumber(s) << endl;
    }
    {
        string s = "B";
        cout << o.titleToNumber(s) << endl;
    }
    {
        string s = "AA";
        cout << o.titleToNumber(s) << endl;
    }
    {
        string s = "AB";
        cout << o.titleToNumber(s) << endl;
    }
    return 0;
}
