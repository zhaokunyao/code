#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;



class Solution {
    public:
        int getSum(int a, int b) {
            int sum = a;
            while(b) {
                sum = a ^ b;
                b = (a & b) << 1;
                a = sum;
            }

            return sum;
        }
};

int main() {
    Solution o;
    {
        int a = 10;
        int b = 21;
        cout << o.getSum(a, b) << endl;
    }
    return 0;
}
