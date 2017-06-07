#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
            map <int, int> m1;
            map <int, int> m2;
            vector<int> ret;
            for (auto n: nums1) {
                if (m1.count(n) == 0) {
                    m1[n] = 0;
                }
                m1[n] ++;
            }
            for (auto n: nums2) {
                if (m2.count(n) == 0) {
                    m2[n] = 0;
                }
                m2[n] ++;
            }

            for (auto n: m2) {
                if (m1.count(n.first) > 0) {
                    int k = min(n.second, m1[n.first]);
                    for (int i =0; i<k; i++) {
                        ret.push_back(n.first);
                    }
                }
            }

            return ret;
        }
};

int main() {
    Solution o;
    {
        vector<int> num1    = {1, 2, 2, 1};
        vector<int> nums2   = {2, 2};

        vector<int> ret = o.intersect(num1, nums2);
        for(auto n: ret) {
            cout << n << ",";
        }
        cout << endl;
    }

    return 0;
}
