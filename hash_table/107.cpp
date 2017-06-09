#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        vector<int> findAnagrams(string s, string p) {
            vector<int> res;
            map<char, int> mp;
            map<char, int> ms;
            int ssize   = s.size();
            int psize   = p.size();
            if (ssize < psize) {
                return res;
            }
            for (int i=0; i<psize; i++) {
                if (mp.count(p[i]) == 0) {
                    mp[p[i]] = 0;
                }
                mp[p[i]] ++;

                if (ms.count(s[i]) == 0) {
                    ms[s[i]] = 0;
                }
                ms[s[i]] ++;
            }
            if (mp == ms) {
                res.push_back(0);
            }

            for (int i=psize; i<ssize; i++) {
                // 加入新node, 去掉旧node, 保持window大小
                if (ms.count(s[i]) == 0) {
                    ms[s[i]] = 0;
                }
                ms[s[i]] ++;

                char key = s[i-psize];

                ms[key] --;
                if (ms[key] == 0) {
                    ms.erase(key);
                }

                if (ms == mp) {
                    res.push_back(i-psize+1);
                }
            }


            return res;
        }
};

int main() {
    Solution o;
    {
        string s = "cbaebabacd";
        string p = "abc";
        vector<int> v = o.findAnagrams(s, p);
        for (auto n : v) {
            cout << n <<  ", ";
        }
        cout << endl;
    }
    {
        string s = "abab";
        string p = "ab";
        vector<int> v = o.findAnagrams(s, p);
        for (auto n : v) {
            cout << n <<  ", ";
        }
        cout << endl;
    }

    return 0;
}
