#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int max = 0;
            int length = prices.size();
            int res = 0;
            if (length == 0) {
                return max;
            }
            int buy = 0;
            for (int i =1 ;i<length; i++) {
                if (prices[i] > prices[i-1]) {
                    max = prices[i] - prices[buy];
                } else {
                    buy = i;
                    res += max;
                    // cout << "adding " << max << endl;
                    max = 0;
                }
            }
            res += max;
            // cout << "adding " << max << endl;
            return res;
        }
};

int main() {
    Solution o;
    {
        vector<int> prices = {6,1,3,2,4,7};
        cout << o.maxProfit(prices) << endl;
    }
    {
        vector<int> prices = {2,4,1};
        cout << o.maxProfit(prices) << endl;
    }
    {
        vector<int> prices = {1,2};
        cout << o.maxProfit(prices) << endl;
    }
    {
        vector<int> prices = {7, 1, 5, 3, 6, 4};
        cout << o.maxProfit(prices) << endl;
    }
    {
        vector<int> prices = {7, 6, 4, 3, 1};
        cout << o.maxProfit(prices) << endl;
    }
    return 0;
}
