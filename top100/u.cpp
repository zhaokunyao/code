#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
        uint32_t reverseBits(uint32_t n) {
            uint32_t m = 0;
            // while(n>0) {
            for (int i =0; i < 32; i++) {
                int b = n & 1;
                n = n >> 1;
                m = (m << 1) | b;
            }
            return m;
        }
};

int main() {
    Solution o;
    {
        uint32_t n = 43261596;
        cout << o.reverseBits(n)<<endl;
    }
    return 0;
}
