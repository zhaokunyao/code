#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
using namespace std;


class Solution {
    public:
        bool searchMatrix(vector<vector<int>>& matrix, int target) {
            int len = matrix.size();
            if (len == 0) return false;
            if (matrix[0].size() == 0) return false;
            int len2 = matrix[0].size();
            int low = len-1;
            int high = 0;
            while(low >=0 && high<len2) {
                if (matrix[low][high] == target) {
                    return true;
                }
                if (matrix[low][high] < target) {
                    high ++;
                } else {
                    low --;
                }
            }

            return false;
        }

};

int main() {
    Solution o;
    {
        vector<vector<int>> matrix = {
            {-1, 3},
        };
        int target = 3;
        cout << o.searchMatrix(matrix, target) << endl;
    }
    {
        vector<vector<int>> matrix = {
            {1,   4,  7, 11, 15},
            {2,   5,  8, 12, 19},
            {3,   6,  9, 16, 22},
            {10, 13, 14, 17, 24},
            {18, 21, 23, 26, 30}
        };
        int target = 5;
        cout << o.searchMatrix(matrix, target) << endl;
    }
    {
        vector<vector<int>> matrix = {
            {1,   4,  7, 11, 15},
            {2,   5,  8, 12, 19},
            {3,   6,  9, 16, 22},
            {10, 13, 14, 17, 24},
            {18, 21, 23, 26, 30}
        };
        int target = 20;
        cout << o.searchMatrix(matrix, target) << endl;
    }
    return 0;
}
