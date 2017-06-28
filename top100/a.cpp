#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            map<char, int> hash;
            int length = s.size();
            int max = 0;
            int j = 0;
            for (int i=0; i< length; i++) {
                auto c = s[i];
                if (!hash.count(c)) {
                    hash[c] = i;
                    auto tmp = i - j +1;
                    if (tmp > max) {
                        max = tmp;
                    }
                    cout << c << "_" << max << "_" << endl;
                    continue;
                }

                if (hash[c] +1 > j)
                    j = hash[c]+1;

                cout << "change j to " << j << endl;
                auto tmp = i - j+1;
                if (tmp > max) {
                    max = tmp;
                }
                hash[c] = i;
            }
            return max;
        }
};

int main() {
    Solution o;
    {
        string s = "nfpdmpi";
        cout << o.lengthOfLongestSubstring(s)<<endl;
    }
    {
        string s = "abba";
        cout << o.lengthOfLongestSubstring(s)<<endl;
    }
    {
        string s = "pwwkew";
        cout << o.lengthOfLongestSubstring(s)<<endl;
    }

    {
        string s = "abcabcbb";
        cout << o.lengthOfLongestSubstring(s)<<endl;
    }
    return 0;
}
