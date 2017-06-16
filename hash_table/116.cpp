#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        int islandPerimeter(vector<vector<int>>& grid) {
            int sum = 0;
            int length = grid.size();
            int length2 = grid[0].size();
            for (int i =0 ;i<length; i++) {
                for (int j =0; j<length2; j++) {
                    if (grid[i][j] == 0) {
                        continue;
                    }
                    if (left(i,j, length, length2,grid)) {
                        sum++;
                    }
                    if (top(i,j, length, length2, grid)) {
                        sum++;
                    }
                    if (right(i,j, length, length2, grid)) {
                        sum++;
                    }
                    if (bottom(i,j, length, length2, grid)) {
                        sum++;
                    }
                }
                // cout << sum << endl;
            }

            return sum;
        }

        bool left(int i, int j, int length, int length2, vector<vector<int>>& grid) {
            if (j == 0) {
                return true;
            }
            if (grid[i][j-1] == 0) {
                return true;
            }
            return false;
        }
        bool right(int i, int j, int length, int length2, vector<vector<int>>& grid) {
            if (j == length2-1) {
                return true;
            }
            if (grid[i][j+1] == 0) {
                return true;
            }
            return false;
        }
        bool top(int i, int j, int length, int length2, vector<vector<int>>& grid) {
            if (i == 0) {
                return true;
            }
            if (grid[i-1][j] == 0) {
                return true;
            }
            return false;
        }
        bool bottom(int i, int j, int length, int length2, vector<vector<int>>& grid) {
            if (i == length-1) {
                return true;
            }
            if (grid[i+1][j] == 0) {
                return true;
            }
            return false;
        }
};

int main() {
    Solution o;
    {
        vector<vector<int>> grid = {
            {0,1}
        };
        cout << o.islandPerimeter(grid) << endl;
    }

    {
        vector<vector<int>> grid = {
            {0,1,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {1,1,0,0}
        };
        cout << o.islandPerimeter(grid) << endl;
    }

    return 0;
}
