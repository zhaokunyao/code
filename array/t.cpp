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
            if (length == 0) {
                return max;
            }
            int buy = 0;
            for (int i =1 ;i<length; i++) {
                if (prices[i] > prices[buy]) {
                    int tmp = prices[i] - prices[buy];
                    if (tmp > max) {
                        max = tmp;
                    }
                } else {
                    buy = i;
                }
            }
            return max;
        }
};

int main() {
    Solution o;
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
