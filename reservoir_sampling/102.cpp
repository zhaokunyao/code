#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

class Solution {
    private: 
        vector<int> nums;
    public:
        Solution(vector<int> nums) {
            this->nums = nums;
            srand(time(NULL));
        }

        int pick(int target) {
            int index   = 0;
            int r       = 0;
            int i       = -1;
            for (auto n : nums) {
                i ++;
                if (n != target) {
                    continue;
                }

                cout << "N:" << n << endl;

                if (index == 0) {
                    r   = i;
                    index ++;
                    continue;
                }

                index ++;
                // cout << rand() << ":" << index << endl;
                if (rand() % index == 0) {
                    r = i;
                }

            }

            return r;
        }
};

int main() {

    vector<int> nums = {1,2,3,3,3};
    Solution * obj = new Solution(nums);
    {
        int param_1 = obj->pick(1);
        cout << param_1 << endl;
    }
    {
        int param_1 = obj->pick(3);
        cout << param_1 << endl;
    }
}
