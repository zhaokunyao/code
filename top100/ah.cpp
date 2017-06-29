#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int findDuplicate(vector<int>& nums) {
            map<int, int> hash;
            for(auto && n: nums) {
                if (hash.count(n) > 0) {
                    return n;
                }
                hash[n] = 1;
            }

            return 0;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2,3,4,5,5};
        cout << o.findDuplicate(nums) << endl;
    }
    return 0;
}
