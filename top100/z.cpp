#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k) {
            map<int, int> hash;
            for (auto && n: nums) {
                hash[n] ++;
            }
            vector<int> res;
            vector<vector<int>> bucket(nums.size() + 1);

            for (auto && pair : hash) {
                bucket[pair.second].push_back(pair.first);
            }

            for (int i=bucket.size()-1; i>=0; i--) {
                for (auto && n : bucket[i]) {
                    res.push_back(n);
                    if (res.size() == k) {
                        return res;
                    }
                }
            }

            return res;

        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,1,1,2,2,3,4};
        int k = 2;
        vector<int> res = o.topKFrequent(nums, k);

        for (auto && n : res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    return 0;
}
