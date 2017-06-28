#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        bool isPowerOfThree(int n) {
            if (n ==0) return false;
            if (n ==1) return true;

            while(true) {
                if (n % 3 != 0) {
                    return false;
                }
                n = n / 3;
                if (n == 1) return true;
            }

            return false;
        }

};

int main() {
    Solution o;
    {
        int n = 27;
        cout << o.isPowerOfThree(n) << endl; // 2
    }
    return 0;
}
