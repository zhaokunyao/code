#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int singleNumber(vector<int>& nums) {
            int s = nums[0];
            int lenght = nums.size();
            for (int i = 1; i<lenght ; i++) {
                s = s xor nums[i];
            }
            return s;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {
            1,3,1,3,5,4,4
        };
        cout << o.singleNumber(nums) << endl;
    }

    return 0;
}
