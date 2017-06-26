#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int findPairs(vector<int>& nums, int k) {
            if (k < 0) {
                return 0;
            }
            map<int, int> hash;
            map<pair<int, int>, int> res;
            for (auto n: nums) {
                hash[n]++;
            }

            if (k == 0) {
                int count = 0;
                for (auto &&pair : hash) {
                    if (pair.second > 1) {
                        count ++;
                    }
                }
                return count;
            }

            for (auto &&n: nums) {
                int p = n + k;
                if (hash[p] >0) {
                    if (p > n ) {
                        swap(p,n);
                    }
                    res[pair<int, int>{p, n}] = 1;
                }
            }

            return res.size();
        }
};

int main() {
    Solution o;

    {
        vector<int> nums = {1,1,1};
        int k = 0;
        cout << o.findPairs(nums, k) << endl;
    }

    {
        vector<int> nums = {3, 1, 4, 1, 5};
        int k = 2;
        cout << o.findPairs(nums, k) << endl;
    }
    {
        vector<int> nums = {1,2,3,4,5};
        int k = 1;
        cout << o.findPairs(nums, k) << endl;
    }
    {
        vector<int> nums = {1, 3, 1, 5, 4};
        int k = 0;
        cout << o.findPairs(nums, k) << endl;
    }
    return 0;
}
