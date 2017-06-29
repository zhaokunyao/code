#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k) {
            vector<int> vec;
            int len = nums.size();
            k = len - k + 1;
            for (int i=0; i<k; i++) {
                vec.push_back(nums[i]);
            }
            std::make_heap(vec.begin(), vec.end());
            for (int i=k; i<len; i++) {
                vec.push_back(nums[i]);
                std::push_heap(vec.begin(), vec.end());
                std::pop_heap(vec.begin(), vec.end());
                vec.pop_back();
            }
            return vec[0];
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {2,3,1,5,6,4};
        int k = 2;
        cout << o.findKthLargest(nums, k)<<endl;
    }
    return 0;
}


