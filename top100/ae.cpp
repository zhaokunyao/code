#include <iostream>
#include <algorithm>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;


class Solution {
    public:
        vector<string> generateParenthesis(int n) {
            vector<vector<string>> res;
            if (n == 0) return vector<string>{};
            res.push_back(vector<string>{"()"});
            for (int i=1; i<=n; i++) {
                vector<string> vec = res[i-1];
                map<string, int> hash;
                for (auto && v : vec) {
                    hash[v+"()"] = 1;
                    hash["()" + v] = 1;
                    hash["("+v+")"] = 1;
                    // hash[v.insert(v.size()/2, ")(")] = 1;
                    // 少了
                }
                vector<string> tmp = {};
                for (auto && pair : hash) {
                    tmp.push_back(pair.first);
                }
                res.push_back(tmp);
            }

            return res[n-1];
        }
};

int main() {
    Solution * o  = new Solution();
    {
        int n = 3;
        vector<string> res = o->generateParenthesis(n);
        for (auto && s : res) {
            cout << s << ", ";
        }
        cout << endl;
    }
    {
        int n = 4;
        vector<string> res = o->generateParenthesis(n);
        for (auto && s : res) {
            cout << s << ", ";
        }
        cout << endl;
    }
    return 0;
}
