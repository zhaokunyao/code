#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
    int trailingZeroes(int n) {
        int count = 0;
        for (long long i =5; n/i > 0 ;i*=5) {
            count += n /i;
            // count += n / pow(5, i);
        }
        return count;
    }


};

int main() {
    Solution o;
    {
        int n = 4;
        cout << o.trailingZeroes(n)<<endl;
    }
    {
        int n = 5;
        cout << o.trailingZeroes(n)<<endl;
    }
    {
        int n = 10;
        cout << o.trailingZeroes(n)<<endl;
    }
    {
        int n = 13;
        cout << o.trailingZeroes(n)<<endl;
    }
    {
        int n = 15;
        cout << o.trailingZeroes(n)<<endl;
    }
    {
        int n = 30;
        cout << o.trailingZeroes(n)<<endl;
    }
    {
        int n = 200;
        cout << o.trailingZeroes(n)<<endl;
    }
    return 0;
}
