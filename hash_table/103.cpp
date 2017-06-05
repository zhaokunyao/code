#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            map<int, int> m;
            vector<int> ret;
            int length = nums.size();

            for (int i =0; i<length; i++) {
                int n = nums[i];
                m[target-n] = i;
            }

            for (int i =0; i<length; i++) {
                int n = nums[i];
                if (m.count(n) > 0) {
                    if (i == m[n]) {
                        continue;
                    }
                    ret =  {i, m[n]};
                    return ret;
                }
            }

            // 其实一次for循环就足够了

            return ret;

        }
};

int main() {
    Solution o;

    {
        vector<int> nums = {2, 7, 11, 15};
        int k = 9;
        vector<int> ret;
        ret = o.twoSum(nums, k);
        cout << ret[0] << endl;
        cout << ret[1] << endl;
    }

    {
        vector<int> nums = {3, 2, 4};
        int k = 6;
        vector<int> ret;
        ret = o.twoSum(nums, k);
        cout << ret[0] << endl;
        cout << ret[1] << endl;
    }
    return 0;
}
