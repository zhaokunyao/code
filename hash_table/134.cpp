#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <stack>
using namespace std;

class Solution {
    public:
        int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
            map<int, int> hash;
            for (auto && i : A) {
                for (auto && j : B ) {
                    int sum = i + j;
                    hash[0-sum]++;
                }
            }

            /**
            for (auto && pair : hash) {
                cout << pair.first << ":" << pair.second << endl;
            }
            **/

            int count = 0;

            for (auto && i : C) {
                for (auto && j : D) {
                    int sum = i + j;
                    count += hash[sum];
                }
            }
            return count;
        }
};

int main() {
    Solution o;
    {
        vector<int> A = {1, 2};
        vector<int> B = {-2,-1};
        vector<int> C = {-1, 2};
        vector<int> D = { 0, 2};
        cout << o.fourSumCount(A, B, C, D) << endl;
    }
    return 0;
}


