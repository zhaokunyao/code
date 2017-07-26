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
        int hIndex(vector<int>& citations) {
            int len = citations.size();
            std::sort(citations.begin(), citations.end(), std::greater<int>());
            for (int i=len; i>0; i--) {
                int count = 0;
                int count2 = 0;
                for(auto && n :citations) {
                    if (n >=i &&count < i) {
                        count++;
                        continue;
                    }
                    if (n <=i) {
                        count2++;
                    }
                }
                // cout << i << ":" << count << ":" << count2 << endl;
                if (count2 + count == len && count == i) {
                    return count;
                }
            }

            return 0;
        }
};

int main() {
    Solution o;
    {
        vector<int> citations = {1, 2};
        cout << o.hIndex(citations) << endl;
    }
    {
        vector<int> citations = {1, 1};
        cout << o.hIndex(citations) << endl;
    }
    {
        vector<int> citations = {5, 5, 5, 5, 5};
        cout << o.hIndex(citations) << endl;
    }
    {
        vector<int> citations = {5, 0, 6, 1, 5};
        cout << o.hIndex(citations) << endl;
    }
    return 0;
}


