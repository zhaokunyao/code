#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    public:
    int searchInsert(vector<int>& nums, int target) {
        int low = 0;
        int length = nums.size();
        
        int high = length-1;
        while(low  <= high) {
            int mid = (high+low )/2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] > target) {
                high = mid-1;
            } else {
                low = mid+1;
            }
        }
        
        return low;
        
    }

};

int main() {
    Solution o;
    {
        vector<int> nums = {1,3,5,6};
        int target = 5;
        cout << o.searchInsert(nums, target);
        cout << endl;
    }
    {
        vector<int> nums = {1,3,5,6};
        int target = 2;
        cout << o.searchInsert(nums, target);
        cout << endl;
    }
    {
        vector<int> nums = {1,3,5,6};
        int target = 7;
        cout << o.searchInsert(nums, target);
        cout << endl;
    }
    {
        vector<int> nums = {1,3,5,6};
        int target = 0;
        cout << o.searchInsert(nums, target);
        cout << endl;
    }
    return 0;
}
