#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int firstUniqChar(string s) {
            map<char, int > hash;
            if (s == "") return -1;
            for (auto && c : s) {
                hash[c] ++;
            }
            int len = s.size();
            for (int i = 0; i<len; i++) {
                if (hash[s[i]] == 1) {
                    return i;
                }
            }
            return -1;
        }
};

int main() {
    Solution o;
    {
        string s = "dacca";
        cout << o.firstUniqChar(s) << endl; // 0
    }
    {
        string s = "leetcode";
        cout << o.firstUniqChar(s) << endl; // 0
    }
    {
        string s = "loveleetcode";
        cout << o.firstUniqChar(s) << endl; // 2
    }
    return 0;
}
