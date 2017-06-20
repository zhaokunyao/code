#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int findMaxConsecutiveOnes(vector<int>& nums) {
            int max = 0; 
            int count = 0;
            for (auto && n : nums) {
                if (n == 0) {
                    if (count > max) {
                        max = count;
                    }
                    count = 0;
                } else {
                    count ++;
                }
            }
            if (count > max) {
                max = count;
            }
            return max;
        }
};

int main() {
    Solution o;

    {
        vector<int> nums = {1,1,0,1,1,1};
        cout << o.findMaxConsecutiveOnes(nums)<<endl;
    }
    return 0;
}
