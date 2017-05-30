#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

class Solution {
    public:
        string removeKdigits(string num, int k) {
            stack<int>sk;
            int length  = num.length();
            if (length == k) {
                return "0";
            }
            for (int i =0; i<length; i++) {
                // pop more
                while(k > 0 && not sk.empty() && (num[i] -'0') < sk.top()) {
                    sk.pop();
                    k--;
                }
                sk.push(num[i]  - '0');
            }

            // k 有可能没用完. 说明后面几个数字都是递增的
            string res;
            while(not sk.empty()) {
                if (k>0) {
                    k--;
                    sk.pop();
                    continue;
                }
                res = to_string(sk.top()) + res;
                sk.pop();
            }

            //remove prefix 0s
            unsigned int i = 0;
            unsigned int l = res.length();
            string r = "";
            for (i=0; i<l; i++) {
                if (res[i] != '0') {
                    break;
                }
            }
            for (; i<l; i++) {
                r += res[i];
            }
            if (r == "") {
                return "0";
            }

            return r;

        }
};

int main() {
    Solution * o = new Solution();
    {
        string num = "112";
        int k = 1;
        cout << o->removeKdigits(num, k) << endl;
    }
    {
        string num = "1432219";
        int k = 3;
        cout << o->removeKdigits(num, k) << endl;
    }
    {
        string num = "10200";
        int k = 1;
        cout << o->removeKdigits(num, k) << endl;
    }
    {
        string num = "120200";
        int k = 1;
        cout << o->removeKdigits(num, k) << endl;
    }
    {
        string num = "120200";
        int k = 2;
        cout << o->removeKdigits(num, k) << endl;
    }
    {
        string num = "120201";
        int k = 3;
        cout << o->removeKdigits(num, k) << endl;
    }
    {
        string num = "10";
        int k = 2;
        cout << o->removeKdigits(num, k) << endl;
    }
    {
        string num = "10";
        int k = 1;
        cout << o->removeKdigits(num, k) << endl;
    }
    return 0;
}
