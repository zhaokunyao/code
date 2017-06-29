#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;


class Solution {
    public:
        int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
            map<int, int> hash;
            int len = A.size();
            for (int i=0; i<len; i++) {
                for (int j=0; j<len; j++) {
                    auto product = A[i] + B[j];
                    hash[0-product]++;
                }
            }
            int count = 0;
            for (int i=0; i<len; i++) {
                for (int j=0; j<len; j++) {
                    auto product = C[i] + D[j];
                    if (hash.count(product) > 0) {
                        count += hash[product];
                    }
                }
            }
            return count;
        }
};

int main() {
    Solution * o  = new Solution();
    {
        vector<int>A = {1, 2};
        vector<int>B = {-2,-1};
        vector<int>C = {-1, 2};
        vector<int>D = {0, 2};
        cout << o->fourSumCount(A, B, C, D) << endl;;
    }

    return 0;
}
