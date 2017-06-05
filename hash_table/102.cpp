#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        bool containsDuplicate(vector<int>& nums) {
            map<int, int> m;
            for (auto n: nums) {
                if (m.count(n)  == 0) {
                    m[n] = 0;
                }
                m[n] ++;
            }

            for (auto mi : m) {
                if (mi.second > 1) {
                    return true;
                }
            }

            return false;
        }
};

int main() {
    Solution o;

    {
        vector<int> nums = {1,2,3,5,4,1};
        cout << o.containsDuplicate(nums)<<endl;
    }
    {
        vector<int> nums = {1,2,3,5,4,6};
        cout << o.containsDuplicate(nums)<<endl;
    }
    return 0;
}
