#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:

        vector<int> getRow(int numRows) {
            if (numRows == 0) {
                return vector<int> {1};
            }
            vector<int> gn = getRow(numRows-1);
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
        vector<int> res;
        int numRows = 0;
        res = o.getRow(numRows);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;

    }
    {
        vector<int> res;
        int numRows = 5;
        res = o.getRow(numRows);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;

    }
    return 0;
}
