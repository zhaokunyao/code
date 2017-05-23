#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
    public:
        int subarraySum(vector<int>& nums, int k) {
            std::map<int,int> map_sum;
            int count = 0;
            int sum = 0;

            map_sum[0] = 1;

            for (auto n : nums) {
                sum += n;
                std::map<int, int>::iterator it;
                it = map_sum.find(sum - k);
                if(it != map_sum.end()) {
                    count += map_sum[sum-k];
                }

                it = map_sum.find(sum);
                if (it != map_sum.end()) {
                    map_sum[sum] ++;
                } else {
                    map_sum[sum] = 1;
                }
            }

            return count;
        }
};


int main() {
    Solution * o = new Solution();
    {
        vector <int> nums;
        nums.push_back(1);
        nums.push_back(1);
        nums.push_back(1);
        int k = 2;
        cout << o->subarraySum(nums, k);
        cout << endl;
    }
    {
        vector <int> nums;
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(0);
        int k = 0;
        cout << o->subarraySum(nums, k);
        cout << endl;
    }
    return 0;
}
