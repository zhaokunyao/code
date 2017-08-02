#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        return f(nums, 0, S);
    }
    int f(vector<int>& nums, int index, int S) {
        int len = nums.size();
        if (index == len) {
            if (S == 0) {
                return 1;
            } else {
                return 0;
            }
        }
        int s1 = S - nums[index];
        int s2 = S + nums[index];
        return f(nums, index+1, s2) + f(nums, index+1, s1);
    }

};

int main() {
    Solution o;

    {
        vector<int> nums = {1, 1, 1, 1, 1};
        int S = 3;
        cout << o.findTargetSumWays(nums, S) << endl;
    }

    return 0;
}
