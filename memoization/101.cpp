#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
    public:
        vector<vector<int>> dp;
        int rows;
        int cols;
        vector<vector<int>> matrix;
        vector<vector<vector<int>>> path;

        int caldp(int i, int j) {

            // 缓存命中
            if (dp[i][j]) {
                return dp[i][j];
            }
            // 取四个方位最大值，再加1
            int ii, jj;
            int mii = -1;
            int mjj = -1;
            int dpiijj;

            ii  = i+1;
            jj  = j;
            if (ii >= rows || (matrix[i][j] >= matrix[ii][jj])) {
            } else {
                dpiijj  = caldp(ii, jj);
                if (dpiijj > dp[i][j]) {
                    dp[i][j] = dpiijj;
                    mii = ii; mjj = jj;
                }
            }

            ii  = i;
            jj  = j+1;
            if (jj >= cols || (matrix[i][j] >= matrix[ii][jj])) {
            } else {
                dpiijj  = caldp(ii, jj);
                if (dpiijj > dp[i][j]) {
                    dp[i][j] = dpiijj;
                    mii = ii; mjj = jj;
                }
            }

            ii  = i;
            jj  = j-1;
            if (jj < 0 || (matrix[i][j] >= matrix[ii][jj])) {
            } else {
                dpiijj  = caldp(ii, jj);
                if (dpiijj > dp[i][j]) {
                    dp[i][j] = dpiijj;
                    mii = ii; mjj = jj;
                }
            }

            ii  = i-1;
            jj  = j;
            if (ii < 0 || (matrix[i][j] >= matrix[ii][jj])) {
            } else {
                dpiijj  = caldp(ii, jj);
                if (dpiijj > dp[i][j]) {
                    dp[i][j] = dpiijj;
                    mii = ii; mjj = jj;
                }
            }
            dp[i][j] ++;
            if (mii != -1 && mjj != -1) {
                path[i][j] = {mii, mjj};
            }

            return dp[i][j];
        }

        int longestIncreasingPath(vector<vector<int>>& matrix) {
            this->matrix    = matrix;
            rows = matrix.size();
            if (rows == 0) {
                return 0;
            }
            cols    = matrix[0].size();

            dp.resize(rows);
            path.resize(rows);
            for (int i =0; i<rows; i++) {
                dp[i].resize(cols);
                path[i].resize(cols);
            }

            for(int i= 0; i<rows; i++) {
                for (int j =0; j<cols; j++) {
                    dp[i][j] = 0;
                    path[i][j] = {};
                }
            }

            // cal dp
            for(int i= 0; i<rows; i++) {
                for (int j =0; j<cols; j++) {
                    caldp(i, j);
                }
            }


            int ret = 0;
            int mi , mj;
            for(int i= 0; i<rows; i++) {
                for (int j =0; j<cols; j++) {
                    if (dp[i][j] > ret) {
                        mi = i; mj=j;
                        ret = dp[i][j];
                    }
                }
            }

            /**
            for(int i= 0; i<rows; i++) {
                for (int j =0; j<cols; j++) {
                    cout << dp[i][j];
                }
                cout << endl;
            }

            for(int i= 0; i<rows; i++) {
                for (int j =0; j<cols; j++) {
                    int size = path[i][j].size();
                    for (int k = 0; k < size; k++) {
                        cout << path[i][j][k] << ",";
                    }
                    cout << "\t";
                }
                cout << endl;
            }
            **/

            string p;

            while(true) {
                p += to_string(matrix[mi][mj]) + ",";
                vector<int> next    = path[mi][mj];
                if (next.size() !=2) {
                    break;
                }

                mi = next[0];
                mj = next[1];
            }

            cout << p << endl;

            return ret;
        }
};

int main() {
    Solution * o = new Solution();
    {
        vector<vector<int>> matrix = {
            {1,2},
            {2,3}
        };
        int n = o->longestIncreasingPath(matrix);
        cout << n << endl;
    }
    {
        vector<vector<int>> matrix = {{9,9,4},
            {6,6,8},
            {2,1,1}};
        int n = o->longestIncreasingPath(matrix);
        cout << n << endl;
    }
    {
        vector<vector<int>> matrix = {
            {3,4,5},
            {3,2,6},
            {2,2,1}
        };
        int n = o->longestIncreasingPath(matrix);
        cout << n << endl;
    }

    return 0;
}
