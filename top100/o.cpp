#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int climbStairs(int n) {
            if (n == 1)  return 1;
            if (n ==2) return 2;
            /**
            return climbStairs(n-1) + climbStairs(n-2);
            **/
            int a = 1;
            int b = 2;
            int c = 0;
            for (int i=3; i<=n; i++) {
                c = a+b;
                a = b;
                b = c;
            }
            return c;
        }
};

int main() {
    Solution o;
    {
        int n = 3;
        cout << o.climbStairs(n) << endl; // 2
    }
    {
        int n = 4;
        cout << o.climbStairs(n) << endl; // 2
    }
    return 0;
}
