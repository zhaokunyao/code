#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int removeElement(vector<int>& nums, int val) {
            int length  = nums.size();
            int p0 =0;
            int p1 =0;

            // p0 points to val
            while(p0<length && p1<length) {
                if (nums[p0] != val) {
                    p0++;
                    continue;
                }
                if (nums[p1] == val) {
                    p1++;
                    continue;
                }
                if (p1 <= p0) {
                    p1++;
                    continue;
                }
                //swap
                std::swap(nums[p0], nums[p1]);
                // p0++;
                // p1++;
            }

            return p0;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {2};
        int val = 3;
        cout << o.removeElement(nums, val)<<endl;
    }

    {
        vector<int> nums = {3, 2, 2, 3};
        int val = 3;
        cout << o.removeElement(nums, val)<<endl;
    }
    return 0;
}
