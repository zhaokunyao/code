#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        vector<vector<int>> subsets(vector<int>& nums) {
            vector<vector<int>> res_vec;
            set<vector<int>> res;
            int len = nums.size();
            if (len == 1) {
                res.insert(nums);
                res.insert(vector<int>{});
                res_vec = convert(res);
                return res_vec;
            }

            for (int i =0; i<len; i++) {
                vector<int> copy = nums;
                copy.erase(copy.begin() + i);
                vector<vector<int>> tmp = subsets(copy);
                for(auto && vec: tmp) {
                    res.insert(vec);
                }
            }
            res.insert(nums);
            res.insert(vector<int>{});
            res_vec = convert(res);
            return res_vec;
        }

        vector<vector<int>> convert(set<vector<int>> s) {
            vector<vector<int>> res;
            for (auto && vec : s) {
                res.push_back(vec);
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2,3,4,5,6,7,8,10,0};
        vector<vector<int>> res = o.subsets(nums);
        for (auto && vec : res) {
            for (auto && n: vec) {
                cout << n << ", ";
            }
            cout << endl;
        }
    }
    {
        vector<int> nums = {1,2,3};
        vector<vector<int>> res = o.subsets(nums);
        for (auto && vec : res) {
            for (auto && n: vec) {
                cout << n << ", ";
            }
            cout << endl;
        }
    }
    return 0;
}
