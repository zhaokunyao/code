#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        void moveZeroes(vector<int>& nums) {
            int i = 0;
            int j = 0;
            int length = nums.size();
            while (j <length && i<length) {
                if (nums[i] != 0) {
                    i++;
                    continue;
                }
                if (nums[j] == 0) {
                    j++;
                    continue;
                }
                if (j < i) {
                    j++;
                    continue;
                }

                int tmp = nums[j];
                nums[j] = nums[i];
                nums[i] = tmp;
            }
        }
};

int main() {
    Solution o;

    {
        vector<int> nums = {0, 1, 0, 3, 12};
        o.moveZeroes(nums);

        for(auto && n :nums) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
