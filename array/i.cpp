#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    public:
        int majorityElement(vector<int>& nums) {
            std::sort(nums.begin(), nums.end());
            int length  = nums.size();
            return nums[length/2];
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {3, 2, 2, 3, 3};
        cout << o.majorityElement(nums)<<endl;
    }
    return 0;
}
