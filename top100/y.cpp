#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
        vector<int> productExceptSelf(vector<int>& nums) {
            vector<int> res;
            int len = nums.size();
            res.push_back(1);
            for (int i=1; i<len; i++) {
                res.push_back(res[i-1] * nums[i-1]);
            }
            int m = 1;
            for (int i=len-2; i>=0; i--) {
                m *= nums[i+1];
                res[i] *= m;
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2,3,4};
        vector<int> res = o.productExceptSelf(nums);

        for (auto && n : res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    return 0;
}
