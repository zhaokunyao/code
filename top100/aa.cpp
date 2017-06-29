#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;


class Solution {
    public:
        vector<int> copy;
        Solution(vector<int> nums) {
            copy = nums;
        }

        /** Resets the array to its original configuration and return it. */
        vector<int> reset() {
            return copy;
        }

        /** Returns a random shuffling of the array. */
        vector<int> shuffle() {
            vector<int> nums2 = copy;
            int len = nums2.size();
            for (int i =0; i < len-1; i++) {
                // int r = i + random() / RAND_MAX * (len-i);
                int r = i + rand() % (len - i);
                std::swap(nums2[i], nums2[r]);
            }
            return nums2;
        }
};

int main() {
    vector<int> nums = {1,2,3};
    Solution * o  = new Solution(nums);
    vector<int> res = o->shuffle();

    for(auto && n : res) {
        cout << n << ",";
    }
    cout << endl;

    res = o->reset();
    for(auto && n : res) {
        cout << n << ",";
    }
    cout << endl;

    return 0;
}
