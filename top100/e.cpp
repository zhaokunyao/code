#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        string reverseString(string s) {
            int len = s.size();
            string t ;
            for (int i=len-1; i>=0; i--) {
                t += string(1, s[i]);
            }
            return t;
        }
};

int main() {
    Solution o;
    {
        string s = "1234567";
        cout << o.reverseString(s) << endl;
    }
    return 0;
}
