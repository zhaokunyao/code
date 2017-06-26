#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int maxSubArray(vector<int>& nums) {
            int max = nums[0];
            int sum = nums[0];
            int length = nums.size();
            for (int i=1; i<length; i++){

                if(sum <0) {
                    sum = nums[i];
                } else {
                    sum += nums[i];
                }

                if (sum > max) {
                    max = sum;
                }
            }
            return max;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {-2, 1};
        cout << o.maxSubArray(nums) << endl;
    }
    {
        vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
        cout << o.maxSubArray(nums) << endl;
    }
    return 0;
}
