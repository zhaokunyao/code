#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
        string countAndSay(int n) {
            string res = "1";
            for (int i=2; i<=n; i++) {
                int len = res.size();
                string tmp = "";
                for (int j=0; j<len; j++) {
                    int k = 1;
                    while(j+k < len) {
                        if (res[j+k] != res[j]) {
                            break;
                        }
                        k++;
                    }
                    tmp += to_string(k) + res[j];
                    j  += k-1;
                }
                res  = tmp;
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        int n = 2;
        cout << o.countAndSay(n)<<endl;
    }
    {
        int n = 3;
        cout << o.countAndSay(n)<<endl;
    }
    {
        int n = 4;
        cout << o.countAndSay(n)<<endl;
    }
    return 0;
}
