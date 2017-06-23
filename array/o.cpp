#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    public:
        int missingNumber(vector<int>& nums) {
            int sum = 0;
            int length = nums.size();
            for (auto && n: nums) {
                sum += n;
            }
            return (length + 1) * length /2 - sum;
        }

        int missingNumber2(vector<int>& nums) {
            int length  = nums.size();
            bool find0  = false;
            for (int i =0 ;i<length; i++) {
                if (nums[i] == 0) {
                    find0 = true;
                    continue;
                }
                int n = nums[i];
                if (nums[n-1] == 0) {
                    nums[n-1] = - 1;
                } else {
                    nums[n-1] *= -1;
                }
            }
            if (!find0) {
                return 0;
            }

            for (int i =0 ;i<length; i++) {
                if (nums[i] >= 0) {
                    return i+1;
                }
            }

            return length;

        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2};
        cout << o.missingNumber(nums) << endl;   // 0
    }
    {
        vector<int> nums = {0,2,3};
        cout << o.missingNumber(nums) << endl;   // 1
    }
    {
        vector<int> nums = {0,1,2};
        cout << o.missingNumber(nums) << endl;   // 3
    }
    {
        vector<int> nums = {0,1,3};
        cout << o.missingNumber(nums) << endl;   // 2
    }
    {
        vector<int> nums = {0};
        cout << o.missingNumber(nums) << endl;   // 1
    }
    return 0;
}
