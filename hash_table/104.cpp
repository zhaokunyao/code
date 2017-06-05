#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int longestPalindrome(string s) {
            int k = 0;
            map<char, int> hash;
            if (s.length() == 0) {
                return 0;
            }
            for (auto c : s) {
                if (hash.count(c) == 0) {
                    hash[c] = 0;
                }
                hash[c] ++;
            }

            int has_1 = 0;
            for (auto h : hash) {
                if (h.second %2 == 1) {
                    has_1   = 1;
                }
                k += (h.second / 2);
            }
            return k * 2 + has_1;
        }
};

int main() {
    Solution o;

    {
        string s = "abccccdd";
        cout << s<< o.longestPalindrome(s) << endl;
    }

    {
        string s = "ccc";
        cout << s<< o.longestPalindrome(s) << endl;
    }
    return 0;
}
