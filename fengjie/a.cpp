#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
using namespace std;


class Solution {
    public:

    int findCount(vector<pair<int, int>> vec, int min_path, int from, int to) {
        if (min_path == 1) {
            for (auto && p : vec) {
                int v1 = std::get<0>(p);
                int v2 = std::get<1>(p);
                if (v1 > v2) {
                    std::swap(v1, v2);
                }
                if (v1 == from && v2 == to) {
                    return 1;
                }
            }

            return 0;
        }

        int c = 0;

        for (auto && p : vec) {
            int v1 = std::get<0>(p);
            int v2 = std::get<1>(p);
            if (v1 == to) {
                c += findCount(vec, min_path-1, from, v2);
            }
            if (v2 == to) {
                c += findCount(vec, min_path-1, from, v1);
            }
        }

        return c;
    }
};

int main() {
    Solution o;
    {
        vector<pair<int, int>> vec = {
            {0,1},
            {0,2},
            {1,3},
            {2,3},

            {2,4},
            {3,5},
            {4,5},

            {4,6},
            {5,7},
            {6,7},

            {8,9},
            {8,10},
            {9,11},
            {10,11},

            {10, 12},
            {11, 13},
            {12, 13},

            {12, 14},
            {13, 15},
            {14, 15},

            {3, 10},
            {5, 12},
            {7, 14},
        };
        int min_path = 3;
        int count = o.findCount(vec, min_path, 0, 5);
        cout << count << endl;
    }
}
