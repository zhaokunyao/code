#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k) {
            int len = nums.size();
            map<int, int> hash;
            for (int i =0;i <len; i++) {
                hash[nums[i]]++;
            }
            vector<vector<int>> bucket(len+1);
            for (auto && pair: hash) {
                bucket[pair.second].push_back(pair.first);
            }
            vector<int>res;

            for (int i=len; i>=0; i--) {
                for (auto n : bucket[i]) {
                    res.push_back(n);
                    k --;
                    if (k == 0) return res;
                }
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,1,1,2,2,3};
        int k = 2;
        vector<int> res = o.topKFrequent(nums, k);
        for (auto && n: res) {
            cout << n << ",";
        }
        cout << endl;
    }

    {
        vector<int> nums = {1,1,1,2,2,3};
        int k = 2;
        o.topKFrequent(nums, k);
    }
    return 0;
}
