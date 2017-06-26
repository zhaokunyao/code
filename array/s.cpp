#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int maxDistance(vector<vector<int>>& arrays) {
            int length = arrays.size();
            int distance = -1;
            for (int i=0 ;i<length; i++) {
                for (int j =0; j<length; j++) {
                    if (i == j) {
                        continue;
                    }
                    int tmp = abs(arrays[i].back()  -  arrays[j][0]);
                    if (tmp > distance) {
                        distance = tmp;
                    }
                }
            }
            return distance;
        }
};

int main() {
    Solution o;
    {
        vector<vector<int>> nums = { 
            {1,5},
            {3,4}
        };
        cout << o.maxDistance(nums) << endl;
    }
    {
        vector<vector<int>> nums = { 
            {1,2,3},
            {4,5},
            {1,2,3}
        };
        cout << o.maxDistance(nums) << endl;
    }

    return 0;
}
