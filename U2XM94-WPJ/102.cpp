#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;


map<std::string, int> hhh;

int foo(vector< vector<int>> & A, int len_row, int len_col) {
    if (len_row == 0 && len_col ==0) return 1;

    int max_count = 0;
    string key = to_string(len_row) + "_" + to_string(len_col);
    if (hhh.count(key) > 0) {
        return hhh[key];
    }

    for (int i = 0; i<=len_row; i++) {
        for (int j=0; j<=len_col; j++) {
            int count_1 = 0;
            int count_2 = 0;
            int count_3 = 0;
            if (i >0 && j>0 ) {
                if (A[i][j] > A[i-1][j-1]) {
                    count_1 = foo(A, i-1, j-1) +1;
                }
                if (A[i][j] > A[i-1][j]) {
                    count_2 = foo(A, i-1, j)+1;
                }
                if (A[i][j] > A[i][j-1]) {
                    count_3 = foo(A, i, j-1)+1;
                }
            } else if (i >0 ) {
                if (A[i][j] > A[i-1][j]) {
                    count_2 = foo(A, i-1, j)+1;
                }
            } else if (j >0) {
                if (A[i][j] > A[i][j-1]) {
                    count_3 = foo(A, i, j-1)+1;
                }
            }
            if (count_1> max_count) max_count = count_1;
            if (count_2> max_count) max_count = count_2;
            if (count_3> max_count) max_count = count_3;
        }
    }
    hhh[key] = max_count;
    // cout << " set " << key << " to " << max_count << endl;
    return max_count;
}

int solution(vector< vector<int> > &A) {
    hhh.clear();
    // write your code in C++14 (g++ 6.2.0)
    int len_row = A.size();
    if (len_row == 0) return 0;
    int len_col = A[0].size();
    if (len_col == 0) return 0;
    return foo(A, len_row-1, len_col-1);

}

int main() {
    {
        vector<vector<int>> A = {{1},{2},{3},{4},{5},{6},{7},{8}};
        cout << solution(A)<< endl;
    }
    {
        vector<vector<int>> A = {{1,2,3,4,5,6,7,8}};
        cout << solution(A)<< endl;
    }
    {
        vector<vector<int>> A = {};
        cout << solution(A)<< endl;
    }
    {
        vector<vector<int>> A = {
            {7, -2, 0, 4, 2},
            {-1, 0, 1, 3, 1},
            {1,  2, 1,-1, 2},
            {4,  0, 0,-3, 0}
        };
        cout << solution(A)<< endl;
    }
    return 0;
}

