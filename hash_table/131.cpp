#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
    int lengthOfLongestSubstring(string s) {
        map<char, int> hash;
        int len = s.size();
        int max = 0;
        int j = -1;
        for (int i=0; i<len; i++) {
            char c = s[i];
            if (hash.count(c) == 0) {
                hash[c] = i;
                if (i-j>max) max = i-j;
                continue;
            }

            if (hash[c] > j) {
                if (i-hash[c] > max) max = i-hash[c];
                j = hash[c];
                hash[c] = i;
                continue;
            }

            if (i-j >max) max = i-j;
            hash[c] = i;
        }
        return max;
    }
};

int main() {
    Solution o;

    {
        string s = "abcabcbb";
        cout << o.lengthOfLongestSubstring(s)<<endl;
    }
    {
        string s = "bbb";
        cout << o.lengthOfLongestSubstring(s)<<endl;
    }
    {
        string s = "pwwkew";
        cout << o.lengthOfLongestSubstring(s)<<endl;
    }
    return 0;
}
