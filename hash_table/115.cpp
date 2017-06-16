#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        char findTheDifference(string s, string t) {
            map<char, int> hash;

            for (auto &&n:s) {
                hash[n] ++;
            }

            for (auto &&n:t) {
                if (hash.count(n) == 0) {
                    return n;
                }

                hash[n] --;
            }

            for (auto pair: hash) {
                if (pair.second < 0) {
                    return pair.first;
                }
            }

            return ' ';
        }
};

int main() {
    Solution o;

    {
        string s = "abcd";
        string t = "abcde";
        cout << o.findTheDifference(s, t) << endl;
    }

    {
        string s = "a";
        string t = "aa";
        cout << o.findTheDifference(s, t) << endl;
    }
    {
        string s = "aa";
        string t = "a3a";
        cout << o.findTheDifference(s, t) << endl;
    }

    return 0;
}
