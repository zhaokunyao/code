#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        bool containsNearbyDuplicate(vector<int>& nums, int k) {
            int length = nums.size();
            map<int, int> hash;
            for (int i=0; i< length; i++) {
                if (i <= k) {
                } else {
                    // remove old 
                    int key = nums[i-k-1];
                    if (hash.count(key) >0) {
                        hash[key] = 0;
                    }
                }

                // add new
                int key = nums[i];
                if (hash.count(key) > 0 && hash[key] ==1) {
                    return true;
                }
                hash[key] = 1;
            }

            return false;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2,1};
        cout << o.containsNearbyDuplicate(nums, 1) << endl;
    }
    {
        vector<int> nums = {1, 1};
        cout << o.containsNearbyDuplicate(nums, 1) << endl;
    }
    {
        vector<int> nums = {1,1,3};
        cout << o.containsNearbyDuplicate(nums, 1) << endl;
    }
    {
        vector<int> nums = {2,2};
        cout << o.containsNearbyDuplicate(nums, 3) << endl;
    }

    return 0;
}
