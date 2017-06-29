#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;


class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            map<int, vector<int>> hash;
            map<string, int> hash2;
            map<string,int >hashtt;
            int len = nums.size();
            for (int i=0; i<len; i++) {
                hash[0-nums[i]].push_back(i);
            }
            vector<vector<int>> res;
            for (int i=0; i<len; i++) {
                for (int j=1; j<len; j++) {
                    if (i == j) continue;
                    string tt = to_string(i) + "_" + to_string(j);
                    if (hashtt.count(tt) >0) {
                        continue;
                    }
                    auto sum = nums[i] + nums[j];
                    if (hash.count(sum) >0) {
                        // cout << "has sum " << sum << ": " << nums[i] << "+" << nums[j] << endl;
                        for (auto && n: hash[sum]) {
                            if (i !=n && j != n) {
                                vector<int> tmp = {nums[i], nums[j], nums[n]};
                                std::sort(tmp.begin(), tmp.end());
                                string s = "";
                                for (auto t : tmp) {
                                    s += to_string(t) + "_";
                                }
                                if (hash2[s] ==0) {
                                    res.push_back(tmp);
                                    hash2[s] = 1;
                                }
                            }
                        }
                    }
                    hashtt[tt] = 1;
                }
            }
            return res;
        }
};

int main() {
    Solution * o  = new Solution();
    {
        vector<int> nums = {2,0,-2,3,-3,0,0};
        vector<vector<int>> res = o->threeSum(nums);
        for (auto && vec: res) {
            for (auto && n: vec) {
                cout << n << ",";
            }
            cout << endl;
        }
    }
    {
        vector<int> nums = {-1, 0, 1, 2, -1, -4};
        vector<vector<int>> res = o->threeSum(nums);
        for (auto && vec: res) {
            for (auto && n: vec) {
                cout << n << ",";
            }
            cout << endl;
        }
    }

    return 0;
}
