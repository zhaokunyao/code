#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        string longestPalindrome(string s) {
            int len = s.size();
            if (len == 0) return "";
            if (len == 1) return s;
            int max = 0;
            int l   = 0;
            int h   = 0;
            for (int i=0; i<len-1; i++) {
                {
                    // odd
                    int low = i;
                    int high = i;
                    while(low >=0 && high <len && s[low] == s[high]) {
                        low --;
                        high ++;
                    }
                    if (high-low-1 >max) {
                        max = high - low-1;
                        l = low+1;
                        h = high-1;
                        // cout << l << ":" <<h << endl;
                    }
                }
                {
                    // even
                    int low = i;
                    int high = i+1;
                    while(low >=0 && high <len && s[low] == s[high]) {
                        low --;
                        high ++;
                    }
                    if (high-low-1 >max) {
                        max = high - low-1;
                        l = low+1;
                        h = high-1;
                        // cout << l << ":" <<h << endl;
                    }
                }
            }

            return s.substr(l, h-l+1);
        }
};

int main() {
    Solution o;
    {
        string s = "babad";
        cout << o.longestPalindrome(s)<<endl;    // bab
    }
    {
        string s = "cbbd";
        cout << o.longestPalindrome(s)<<endl;    // bb
    }
    return 0;
}
