#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        vector<int> findDisappearedNumbers(vector<int>& nums) {
            int length = nums.size();
            vector<int> res;
            for(int i=0; i<length; i++) {
                int n = nums[i];
                if (n < 0) {
                    n *= -1;
                }
                if (nums[n-1] >0) {
                    nums[n-1] *= -1;
                }
                cout << n  << " making nums[" << n-1 <<  "]: "<< nums[n-1]<<"  * -1 " << endl;
            }

            for(int i=0; i<length; i++) {
                int n = nums[i];
                if (n > 0) {
                    res.push_back(i+1);
                }
            }
            return res;
        }
};

int main() {
    Solution o;

    {
        vector<int> nums = {4,3,2,7,8,2,3,1};
        vector<int> res = o.findDisappearedNumbers(nums);
        for (auto &&n: res) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
