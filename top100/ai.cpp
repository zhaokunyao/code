#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        vector<vector<int>> permute(vector<int>& nums) {
            int len = nums.size();
            vector<vector<int>> res;
            if (len == 1) {
                res.push_back(nums);
                return res;
            }
            for (int i =0; i< len; i++) {
                vector<int>tmp = nums;
                tmp.erase(tmp.begin() + i);
                vector<vector<int>> vecs = permute(tmp);
                for (auto && vec : vecs) {
                    vec.push_back(nums[i]);
                    res.push_back(vec);
                }
            }

            return res;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2,3};
        vector<vector<int>> res = o.permute(nums);
        for (auto && vec : res) {
            for (auto && n: vec) {
                cout << n << ", ";
            }
            cout << endl;
        }
    }
    return 0;
}
