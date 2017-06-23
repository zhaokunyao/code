#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> copy = nums;
        std::sort(copy.begin(), copy.end());
        int  i = 0;
        int p0  = 0;
        int p1  = 0;
        for (auto && n: copy) {
            if (nums[i] != n) {
                if (p0 == 0) {
                    p0 = i+1;
                }
                p1  = i;
            }
            i++;
        }

        return p1-p0+1+1;
    }
};

int main() {
    Solution o;
    {
        vector<int> nums = {2,3,3,2,4};
        cout << o.findUnsortedSubarray(nums) << endl;   // 3
    }
    {
        vector<int> nums = {1,3,2,1,1};
        cout << o.findUnsortedSubarray(nums) << endl;   // 4
    }
    {
        vector<int> nums = {1,3,2,3,3};
        cout << o.findUnsortedSubarray(nums) << endl;   // 2
    }
    {
        vector<int> nums = {1,3,2,2,2};
        cout << o.findUnsortedSubarray(nums) << endl;   // 4
    }
    {
        vector<int> nums = {1,3,2,4,5};
        cout << o.findUnsortedSubarray(nums) << endl;   // 2
    }
    {
        vector<int> nums = {2,1};
        cout << o.findUnsortedSubarray(nums) << endl;   // 2
    }
    {
        vector<int> nums = {2, 6, 4, 8, 10, 9, 15};
        cout << o.findUnsortedSubarray(nums) << endl;   // 5
    }
    return 0;
}
