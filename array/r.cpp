#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        bool canPlaceFlowers(vector<int>& flowerbed, int n) {
            int count = 0;
            int count_prefix_0 = 0;
            bool has_1   = false;
            int length = flowerbed.size();
            int i = 0;
            for ( auto && f: flowerbed) {
                if (f == 1) {
                    has_1   = true;
                    break;
                }
                count_prefix_0 ++;
                i++;
            }
            if (!has_1) {
                count = (1+count_prefix_0) / 2;
                return count >= n;
            }
            count += (count_prefix_0) / 2;
            int count_inner_0 = 0;
            for (;i < length; i++) {
                if (flowerbed[i] == 1) {
                    count += (count_inner_0 -1)/2;
                    count_inner_0 = 0;
                } else {
                    count_inner_0 ++;
                }
            }

            if (count_inner_0 > 0) {
                count += (count_inner_0) / 2;
            }

            return count >=n ;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {0,0,0};
        int k = 2;
        cout << o.canPlaceFlowers(nums, k) << endl;
    }

    {
        vector<int> nums = {1,0,0,0,1};
        int k = 1;
        cout << o.canPlaceFlowers(nums, k) << endl;
    }
    {
        vector<int> nums = {1,0,0,0,1};
        int k = 2;
        cout << o.canPlaceFlowers(nums, k) << endl;
    }

    return 0;
}
