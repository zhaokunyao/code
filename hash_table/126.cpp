#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        int findMaxLength(vector<int>& nums) {
            map<int, int> hash;
            int length = nums.size();
            int count_0 = 0;
            int count_1 = 0;
            int max  = 0;

            hash[0] = -1;

            for (int i =0; i<length ; i++) {
                int n = nums[i];
                if (n == 0) {
                    count_0 ++;
                } else {
                    count_1 ++;
                }

                auto c = count_1 - count_0;
                if (hash.find(c)!=hash.end()) {
                    auto tmp = i - hash[c];
                    if (tmp > max) {
                        max = tmp;
                    }
                } else {
                    hash[c] = i;
                }
            }
            return max;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {0, 1};
        cout << o.findMaxLength(nums)<<endl;
    }
    return 0;
}
