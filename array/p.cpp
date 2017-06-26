#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            int p1  = m-1;
            int p2  = n-1;
            int k   = m+n-1;
            while(p1 >=0 && p2 >=0) {
                if (nums1[p1] >= nums2[p2]) {
                    nums1[k]   = nums1[p1];
                    p1--;
                } else {
                    nums1[k]   = nums2[p2];
                    p2--;
                }
                k--;
            }
            if (p2 >=0 ){
                for (; p2 >=0; p2--) {
                    nums1[k] = nums2[p2];
                    k--;
                }
            }
        }
};

int main() {
    Solution o;

    {
        vector<int> nums1 = {0};
        int m = 0;
        vector<int> nums2 = {1};
        int n = 1;
        o.merge(nums1, m, nums2, n);
        for(auto && n : nums1) {
            cout << n << ",";
        }
        cout << endl;
    }
    {
        vector<int> nums1 = {2,4,6,8,0,0,0,0};
        int m = 4;
        vector<int> nums2 = {1,3,5,7};
        int n = 4;
        o.merge(nums1, m, nums2, n);
        for(auto && n : nums1) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
