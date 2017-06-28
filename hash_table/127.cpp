#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            map<string, vector<int>> hash;

            int i =0;
            for (auto  s : strs) {
                // cout << i  << ":";
                std::sort(s.begin(), s.end());
                // cout << s ;
                if (hash.count(s) ==0) {
                    // cout << " init ";
                    hash[s] = vector<int>{};
                }
                hash[s].push_back(i++);
                // cout << " push back " << i-1;
                // cout << endl;
            }

            vector<vector<string>> res;

            i = 0;
            for (auto && pair : hash) {
                res.push_back(vector<string>{});
                for (auto && j : pair.second) {
                    res[i].push_back(strs[j]);
                }
                i++;
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
        vector<vector<string>> res = o.groupAnagrams(strs);
        for (auto && vec : res) {
            for (auto && s: vec) {
                cout << s << ",";
            }
            cout << endl;
        }
    }
    return 0;
}
