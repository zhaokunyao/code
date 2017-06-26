#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        vector<vector<int>> generate(int numRows) {
            if (numRows == 0) {
                return vector<vector<int>>{};
            }
            vector<vector<int>> res = {{1}};
            for (int i =1 ;i<numRows; i++) {
                int length = res[i-1].size();

                vector<int>tmp;
                tmp.push_back(1);
                for (int j =0 ;j<length-1; j++) {
                    tmp.push_back(res[i-1][j] + res[i-1][j+1]);
                }
                tmp.push_back(1);
                res.push_back(tmp);
            }
            return res;
        }

        vector<vector<int>> generate2(int numRows) {
            vector<vector<int>> res;
            for (int i =1 ;i<=numRows; i++) {
                vector<int> tmp = g(i);
                res.push_back(tmp);
            }
            return res;
        }

        vector<int> g(int numRows) {
            if (numRows == 1) {
                return vector<int> {1};
            }
            vector<int> gn = g(numRows-1);
            int length= gn.size();
            vector<int>res;
            res.push_back(1);
            for (int i =0 ;i<length-1; i++) {
                res.push_back(gn[i] + gn[i+1]);
            }
            res.push_back(1);

            return res;
        }
};

int main() {
    Solution o;
    {
        vector<vector<int>> res;
        int numRows = 5;
        res = o.generate(numRows);

        for(auto && vec: res) {
            for (auto && n : vec) {
                cout << n << ", ";
            }
            cout << endl;
        }
    }
    return 0;
}
