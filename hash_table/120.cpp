#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        vector<string> findRepeatedDnaSequences(string s) {
            vector<string> res;
            map<string, int> hash;
            vector<char> c10;

            int i = 0;
            for (auto c: s) {
                i++;
                if (i < 10) {
                    // push
                    c10.push_back(c);
                    continue;
                }
                if (i == 10) {
                    // join and set map
                    c10.push_back(c);
                    char * p = c10.data();
                    p[10] = '\0';
                    string sp(p);
                    cout << " hit 10 " << c10.size() << " " << sp << endl;
                    hash[sp] ++;
                    continue;
                }
                // pop left
                c10.erase(c10.begin());
                // push right
                c10.push_back(c);
                // join and set map
                char * p = c10.data();
                p[10] = '\0';
                string sp(p);
                hash[sp] ++;
            }

            for (auto &&pair : hash) {
                cout << pair.first.length() << endl;
                if (pair.second > 1) {
                    res.push_back(pair.first);
                }
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<string> res;
        string s =  "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        res = o.findRepeatedDnaSequences(s);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;
    }
    {
        vector<string> res;
        string s =  "AAAAAAAAAAA";
        res = o.findRepeatedDnaSequences(s);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;
    }

    return 0;
}
