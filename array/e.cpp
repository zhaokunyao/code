#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        vector<int> twoSum(vector<int>& numbers, int target) {
            int p1  =0 ;
            int length = numbers.size();
            int p2  =length -1;
            while(true) {
                if (numbers[p1] + numbers[p2] == target) {
                    break;
                }
                if (numbers[p1] + numbers[p2] > target) {
                    p2 --;
                } else {
                    p1++;
                }
            }

            return vector<int> {p1+1, p2+1};
        }
};

int main() {
    Solution o;

    {
        vector<int> nums = {2,7, 11, 19};
        vector<int> res = o.twoSum(nums, 18);

        for(auto && n :res) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
