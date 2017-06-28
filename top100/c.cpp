#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int reverse(int x) {
            long long y = 0;
            bool isM = 0;
            if (x < 0) {
                x = x * -1;
                isM = 1;
            }
            while(x>0) {
                auto mod = x % 10;
                x = x / 10;
                y = y * 10 + mod;
                if (y > INT_MAX) {
                    return 0;
                }
            }

            if (isM) {
                y = y * -1;
            }
            return y;
        }
};

int main() {
    Solution o;
    {
        int x = 1534236469;
        cout << o.reverse(x)<<endl;
    }
    {
        int x = 123;
        cout << o.reverse(x)<<endl;
    }
    {
        int x = -123;
        cout << o.reverse(x)<<endl;
    }
    return 0;
}
