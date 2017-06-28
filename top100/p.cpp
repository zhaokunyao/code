#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int hammingWeight(uint32_t n) {
            int sum = 0;
            while(n >0) {
                if (n & 1) {
                    sum ++;
                }
                n = n >> 1;
            }
            return sum;
        }
};

int main() {
    Solution o;
    {
        int n = 3;
        cout << o.hammingWeight(n) << endl; 
    }
    {
        int n = 4;
        cout << o.hammingWeight(n) << endl;
    }
    return 0;
}
