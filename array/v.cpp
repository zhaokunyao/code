#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
            
            vector<vector<int>> res;
            int count = 0;
            int ri = -1;
            for (auto &vec : nums) {
                for (auto &&n:vec) {
                    if (count % c == 0) {
                        vector<int> tmp;
                        res.push_back(tmp);
                        ri++;
                    }
                    res[ri].push_back(n);
                    count ++;
                }
            }
            if (count != r*c) {
                return nums;
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<vector<int>> nums = {
        {1,2},
         {3,4}
        };
        int r = 1;
        int c = 4;
        vector<vector<int>> res = o.matrixReshape(nums, r, c);
        for (auto & vec : res) {
            for (auto & n : vec) {
                cout << n << ", ";
            }
            cout << endl;
        }
    }
    return 0;
}
