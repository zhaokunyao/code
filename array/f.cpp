#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            int i = 0;
            int j = 0;
            int length = nums.size();
            if (length == 0) {
                return 0;
            }
            while (i < length-1) {
                if (nums[i] == nums[i+1]) {
                    break;
                }
                i++;
            }

            i++;
            j = i+1;
            while (j < length) {
                if (nums[j]  != nums[i]) {
                    break;
                }
                j ++;
            }
            cout << ":"<<i << ":" <<j<<endl;
            int old = nums[j];
            while(i<length && j<length) {
                nums[i] = nums[j];
                old  = nums[j];
                i ++;
                j ++;
                while(j <length && nums[j] == old) {
                    j++;
                }
            }

            return i;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2,2};
        int n = o.removeDuplicates(nums);
        cout << n << endl;

        for(auto && n :nums) {
            cout << n << ",";
        }
        cout << endl;
    }

    {
        vector<int> nums = {1,1,2,2,3};
        int n = o.removeDuplicates(nums);
        cout << n << endl;

        for(auto && n :nums) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
