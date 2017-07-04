#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> digits = {0,1,2,3,4,5,6,7,8,9};
    for (auto && d: digits) {
        for (auto && e: digits) {
            int top = d*100 + 70 + e;
            for (auto && f: digits) {
                int level_1 = top * f;
                if (level_1 % 10 !=0 || level_1 / 100 !=18) {
                    continue;
                }

                for (auto && g: digits) {
                    int top2 = g * 10 + f;
                    int product = top * top2;
                    if (top * top2 / 1000 == 32) {
                        cout << top << "x" << top2 << "="<<product << endl;
                    }
                }
            }
        }
    }
    return 0;
}
