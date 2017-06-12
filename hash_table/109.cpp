#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
    public:
        map<int, int> hash;
        int numberOfBoomerangs(vector<pair<int, int>>& points) {
            int count = 0;
            int length = points.size();
            for (int i=0; i <length; i++) {
                hash.clear();
                for (int j = 0; j<length; j++) {
                    int dis = getDistance(points[i], points[j]);
                    // cout << i << "::" << j << "~" << dis <<  endl;
                    if (hash.count(dis) == 0){
                        hash[dis] = 0;
                    }
                    hash[dis] ++;
                }
                for (auto node : hash) {
                    count += getCount(node.second);
                }
                // cout << "---------------" << endl;
            }
            return count;
        }

        int getCount(int n) {
            if (n < 1) {
                return 0;
            }

            return n * (n-1);
        }

        int getDistance(pair<int, int>&a, pair<int, int>&b) {
            int aa = a.first - b.first;
            int bb = a.second - b.second;
            return aa*aa + bb*bb;
        }
};

int main() {
    Solution o;
    {
        vector<pair<int, int>> points;
        points.push_back(pair<int, int>{0, 0});
        points.push_back(pair<int, int>{1, 0});
        points.push_back(pair<int, int>{2, 0});
        cout << o.numberOfBoomerangs(points)<<endl;
    }
    {
        vector<pair<int, int>> points;
        points.push_back(pair<int, int>{0, 0});
        points.push_back(pair<int, int>{1, 0});
        points.push_back(pair<int, int>{-1, 0});
        points.push_back(pair<int, int>{0, 1});
        points.push_back(pair<int, int>{0, -1});
        cout << o.numberOfBoomerangs(points)<<endl;
    }
    return 0;
}
