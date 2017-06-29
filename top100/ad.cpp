#include <iostream>
#include <algorithm>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;


class Solution {
    public:
        int kthSmallest(vector<vector<int>>& matrix, int k) {
            vector<int> res;
            for (auto && vec: matrix) {
                for (auto && n: vec) {
                    res.push_back(n);
                }
            }
            std::sort(res.begin(), res.end());
            return res[k-1];
        }
};

int main() {
    Solution * o  = new Solution();
    {
        vector<vector<int>> matrix = {
            { 1,  5,  9},
            {10, 11, 13},
            {12, 13, 15}
        };
        int k = 7;
        cout << o->kthSmallest(matrix, k) << endl; 
    }

    {
        vector<vector<int>> matrix = {
            { 1,  5,  9},
            {10, 11, 13},
            {12, 13, 15}
        };
        int k = 8;
        cout << o->kthSmallest(matrix, k) << endl; 
    }
    return 0;
}
