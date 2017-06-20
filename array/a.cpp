#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int thirdMax(vector<int>& nums) {
            set<int> s;
            for (auto &&n: nums) {
                s.insert(n);
                if (s.size() > 3) {
                    s.erase(s.begin());
                }
            }

            if (s.size() == 3) {
                return *s.begin();
            } else {
                return *s.rbegin();
            }
        }
};

int main() {
    Solution o;

    {
        vector<int> nums = {5, 2, 2};
        cout << o.thirdMax(nums)<<endl;
    }
    {
        vector<int> nums = {3, 2, 1};
        cout << o.thirdMax(nums)<<endl;
    }
    {
        vector<int> nums = {1, 2};
        cout << o.thirdMax(nums)<<endl;
    }
    {
        vector<int> nums = {2, 2, 3, 1};
        cout << o.thirdMax(nums)<<endl;
    }
    return 0;
}
