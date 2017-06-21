#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    public:
        int arrayPairSum(vector<int>& nums) {
            std::sort(nums.begin(), nums.end());
            int sum = 0;
            int length = nums.size();
            for(int i =0 ;i<length; i++ ){
                if (i % 2 == 0) {
                    sum += nums[i];
                }
            }
            return sum;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,4,3,2};
        cout << o.arrayPairSum(nums);
        cout << endl;
    }
    return 0;
}
