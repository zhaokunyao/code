#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
        int strStr(string haystack, string needle) {
            int len = haystack.size();
            int len2 = needle.size();
            if (len < len2) return -1;

            for (int i=0; i<=len-len2; i++) {
                int count = 0;
                for (int j =0; j<len2; j++) {
                    if (haystack[i+j] != needle[j]) {
                        break;
                    }
                    count ++;
                }
                if (count == len2) return i;
            }
            return -1;
        }
};

int main() {
    Solution o;
    {
        string haystack = "abcdef";
        string needle = "def";
        cout << o.strStr(haystack, needle) << endl;
    }
    return 0;
}
