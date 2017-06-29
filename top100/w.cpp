#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
        int mySqrt(int x) {
            int low = 0;
            int high = INT_MAX;
            if (x == 0) {
                return 0;
            }
            while(low <= high) {
                // int mid = (low + high) /2;
                int mid = low + (high-low) /2;
                // cout << high << ":" << low << ":" << mid<< endl;
                // if (mid * mid == x) {
                if (mid == x/mid) {
                    return mid;
                }
                // if (mid *mid > x) {
                if (mid > x/mid) {
                    high = mid - 1;
                } else {
                    low  = mid + 1;
                }
            }
            return low-1;
        }
};

int main() {
    Solution o;
    {
        int x = 4;
        cout  << o.mySqrt(x) << endl;
    }
    {
        int x = 2147395599;
        cout  << o.mySqrt(x) << endl;
    }
    {
        int x = 0;
        cout  << o.mySqrt(x) << endl;
    }
    {
        int x = 10;
        cout  << o.mySqrt(x) << endl;
    }
    {
        int x = 9;
        cout  << o.mySqrt(x) << endl;
    }
    return 0;
}
