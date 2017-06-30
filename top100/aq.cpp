#include <iostream>
#include <algorithm>
#include <limits.h>
#include <map>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        int search(vector<int>& nums, int target) {
            int len  = nums.size();
            int pivot = -1;
            for (int i =0 ;i<len-1; i++) {
                if (nums[i]>nums[i+1]) {
                    pivot = i;
                    break;
                }
            }

            for (int i =0; i<=pivot; i++) {
                nums.push_back(nums[i]);
            }
            // printVec(nums);

            int pos = bs(nums, target, pivot+1);
            // cout << pos << endl;
            if (pos < len) {
                return pos;
            } else {
                return pos - len;
            }
        }

        void printVec(vector<int> nums) {
            for (auto && n : nums) {
                cout << n << ", ";
            }
            cout << endl;
        }

        int bs(vector<int> & nums, int target, int low) {
            int len = nums.size();
            int high = len -1;
            while(low <= high) {
                int mid = (low+high)/2;
                if (nums[mid] == target) {
                    return mid;
                }
                if (nums[mid] > target) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            return -1;
        }

};

int main() {
    Solution o;
    {
        vector<int> nums = {4,5,6,7,0,1,2};
        int target = 5;
        cout << o.search(nums, target) << endl;
    }
    {
        vector<int> nums = {4,5,6,7,0,1,2};
        int target = 2;
        cout << o.search(nums, target) << endl;
    }
    return 0;
}
