#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    public:
        void rotate(vector<int>& nums, int k) {
            int length = nums.size();
            k = k % length;
            if (k == 0) {
                return;
            }
            for (int i = 0; i < k; i++) {
                int c = nums[length-1];
                nums.erase(nums.begin() + length -1);
                nums.insert(nums.begin(), c);
            }
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2,3,4,5,6,7};
        int k = 3;
        o.rotate(nums, k);
        for (auto && n:nums) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
