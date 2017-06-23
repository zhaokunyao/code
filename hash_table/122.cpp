#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        bool cmp(pair<char, int> i, pair<char, int> j) {
            return i.second < j.second;
        }
        string frequencySort(string s) {
            map<char, int> hash;
            string res;
            for (auto && c : s) {
                hash[c]++;
            }

            vector<pair<char, int>> vec(hash.begin(), hash.end());


            std::sort(vec.begin(), vec.end(), [] (pair<char, int> i, pair<char, int>j) {return i.second>j.second;} );

            for (auto && pair : vec) {
                for (int i=0; i< pair.second; i++) {
                    res += string(1, pair.first);
                }
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        string s = "tree";
        cout << o.frequencySort(s) << endl;
    }
    {
        string s = "Aabb";
        cout << o.frequencySort(s) << endl;
    }
    {
        string s = "zxab";
        cout << o.frequencySort(s) << endl;
    }
    return 0;
}
