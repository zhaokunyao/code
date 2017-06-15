#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        bool isHappy(int n) {
            map<int, int> hash;
            while(true) {
                // cout << "push n to hash " << n << endl;
                hash[n] = 1;
                int sum = 0;
                while ( n>0 ) {
                    int m = n % 10;
                    sum += m * m;
                    n = (int) (n/10);
                }
                // cout << sum << endl;

                if (sum == 1) {
                    return true;
                }

                n = sum;
                if (hash[n] ==1) {
                    return false;
                }
            }

            return false;
        }
};

int main() {
    Solution o;

    {
        cout << o.isHappy(3) << endl;
        cout << o.isHappy(19) << endl;
    }

    return 0;
}
