#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        void rotate2(vector<vector<int>>& matrix) {
            vector<vector<int>> m2;
            int len = matrix.size();
            for (int i =0; i< len; i++) {
                m2.push_back(vector<int>{});
                for (int j=0; j<len; j++) {
                    m2[i].push_back(matrix[len-j-1][i]);
                }
            }
            matrix = m2;
        }

        void rotate(vector<vector<int>>& matrix) {
            vector<vector<int>> copy = matrix;
            int len = matrix.size();
            for (int i =0; i< len; i++) {
                for (int j=0; j<len; j++) {
                    matrix[i][j] =   copy[len-j-1][i];
                }
            }
        }
};

int main() {
    Solution o;
    {
        vector<vector<int>> matrix = {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        };
        o.rotate(matrix);
        for (auto && vec: matrix) {
            for (auto && n : vec) {
                cout << n << ",";
            }
            cout << endl;
        }
    }
    return 0;
}
