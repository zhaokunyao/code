#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int distributeCandies(vector<int>& candies) {
            int length = candies.size() / 2;
            map<int, int> hash;
            set<int> my;
            for (auto n : candies) {
                hash[n] ++;
            }

            int sum = 0;
            while (sum <= length) {
                for (auto &&pair : hash) {
                    if (pair.second == 0) {
                        continue;
                    }
                    sum ++;
                    pair.second --;
                    my.insert(pair.first);
                    if (sum == length) {
                        return my.size();
                    }
                }
            }
            return my.size();
        }
};

int main() {
    Solution o;

    {
        vector<int> candies  = {
            1,1,2,2,3,3
        };
        cout << o.distributeCandies(candies) << endl;
    }

    {
        vector<int> candies  = {
            1,1,2,3
        };
        cout << o.distributeCandies(candies) << endl;
    }

    return 0;
}
