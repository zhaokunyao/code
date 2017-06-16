#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        map<char, int> hash;
        vector<string> findWords(vector<string>& words) {
            vector<string> base = {
                "qwertyuiop",
                "asdfghjkl",
                "zxcvbnm"
            };
            for(int i=0; i<3; i++) {
                for (auto n : base[i]) {
                    hash[n] = i;
                }
            }
            vector<string> res;
            for (auto &&w : words) {
                if (ok(w)) {
                    res.push_back(w);
                }
            }
            return res;
        }

        bool ok(string w) {
            int m = hash[tolower(w[0])];
            for (auto n : w) {
                n = tolower(n);
                if (hash[n] != m) {
                    return false;
                }
            }

            return true;
        }
};

int main() {
    Solution o;
    {
        vector<string> words = {
            "Hello", "Alaska", "Dad", "Peace"
        };
        vector<string> res = o.findWords(words);
        for (auto n : res) {
            cout << n << ",";
        }
        cout << endl;
    }

    return 0;
}
