#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        // nums1和nums2已排好序
        vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
            vector<int> ret;
            int i =0;
            int j =0;
            int s1  = (int) nums1.size();
            int s2  = (int) nums2.size();
            while (i<s1 && j<s2) {
                if (nums1[i] == nums2[j]) {
                    ret.push_back(nums2[j]);
                    i++; j++;
                } else {
                    if (nums1[i] < nums2[j]) {
                        i++;
                    } else {
                        j++;
                    }
                }
            }

            // 比merge sort的merge要简单
            // 没有后续流程了

            return ret;
        }
};

int main() {
    Solution o;
    {
        vector<int> num1    = {1, 1, 2, 2};
        vector<int> nums2   = {2, 2};

        vector<int> ret = o.intersect(num1, nums2);
        for(auto n: ret) {
            cout << n << ",";
        }
        cout << endl;
    }

    return 0;
}
