#include <iostream>
#include <algorithm>
#include <limits.h>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Solution {
    public:
        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            map<int, vector<pair<int, int>>> hash;
            int len = nums.size();
            vector<vector<int>> res;
            set<vector<int>> s;

            for (int i =0; i< len; i++) {
                for (int j=0; j<len; j++) {
                    if (i ==j ) continue;
                    int sum = nums[i] + nums[j];
                    hash[target-sum].push_back(make_pair(i, j));
                }
            }

            for (int i =0 ; i<len; i++) {
                for (int j =0; j< len; j++) {
                    if (i == j) continue;
                    int sum = nums[i] + nums[j];
                    if (hash.count(sum) > 0) {
                        for (auto && q: hash[sum]) {
                            if (i == q.first || j ==q.first || i==q.second || j==q.second) continue;
                            vector<int> v;
                            v.push_back(nums[i]);
                            v.push_back(nums[j]);
                            v.push_back(nums[q.first]);
                            v.push_back(nums[q.second]);
                            std::sort(v.begin(), v.end());
                            /**
                            // cout << "pushing ";
                            for (auto && x : v) {
                                cout << x << ", ";
                            }
                            cout << endl;
                            **/
                            s.insert(v);
                        }
                    }
                }
            }
            for (auto&& vec : s) {
                res.push_back(vec);
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1, 0, -1, 0, -2, 2};
        int target = 0;
        vector<vector<int>> res = o.fourSum(nums, target);
        for (auto &&vec : res) {
            for (auto && n : vec) {
                cout << n << ",";
            }
            cout << endl;
        }
    }
    return 0;
}
