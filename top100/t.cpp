#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
        string longestCommonPrefix(vector<string>& strs) {
            string s = "";
            string old = "";
            int len = strs.size();
            if (len ==0) {
                return s;
            }
            int min_len = strs[0].size();
            for(auto  str : strs) {
                int l = str.size();
                if (l < min_len) {
                    min_len = str.size();
                }
            }

            for (int j=1; j<=min_len; j++) {
                s = strs[0].substr(0, j);
                // cout << " Ming " << s << endl;
                for(int i=0; i<len; i++) {
                    if (strs[i].substr(0, j) != s) {
                        return old;
                    }
                }
                old = s;
            }
            return s;
        }
};

int main() {
    Solution o;
    {
        vector<string> strs = {
            "abc",
            "abd",
            "abfe",
        };
        cout << o.longestCommonPrefix(strs)<<endl;
    }
    return 0;
}
