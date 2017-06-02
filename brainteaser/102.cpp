#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
    public:
        /**
        0:0
        1:1
        2:1
        3:1
        4:2
        5:2
        6:2
        7:2
        8:2
        9:3
        10:3
        11:3
        12:3
        13:3
        14:3
        15:3
        16:4
        17:4
        18:4
        19:4
        **/
        int bulbSwitch(int n) {
            if (n < 2) {
                return n;
            }
            return (int)sqrt(n);
        }
        int bulbSwitch2(int n) {
            if (n < 2) {
                return n;
            }
            vector<int> bulbs;
            bulbs.push_back(-1);
            for(int i =1; i<=n; i++) {
                bulbs.push_back(0);
            }
            for (int j =1; j < n; j++) {
                for(int i=1; i<=n; i++) {
                    if (i % j ==0) {
                        bulbs[i] = 1 - bulbs[i];
                    }
                }
            }

            bulbs[n] = 1 - bulbs[n];

            int m = 0;
            for (int i=1; i<=n; i++) {
                if (bulbs[i] == 1) {
                    m ++;
                }
            }

            return m;
        }

};

int main() {
    Solution * o = new Solution();
    for (int n = 0; n < 20; n++) {
        cout << n << ":" << o->bulbSwitch(n) << endl;
    }

    return 0;
}
