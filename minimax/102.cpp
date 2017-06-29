#include <iostream>
#include <map>
#include <vector>

using namespace std;
class Solution {
    public:
        map<int, bool> cache;
        int left;
        int right;

        bool PredictTheWinner(vector<int>& nums) {
            int length  = nums.size();
            if (length == 0 || length == 1) {
                return true;
            }
            left    = 0;
            right   = length - 1;
            vector<int> sum = {0, 0};
            return play(nums, sum);
        }

        bool play(vector<int> &nums, vector<int> &sum) {
            int left_backup     = left;
            int right_backup    = right;
            vector<int> sum_backup = {sum[0], sum[1]};
            cout << "X: " << left << ":" << right<< endl;

            if (left == right) {
                sum[0] += nums[left];
                cout << "eq finish " << sum[0] << ":" << sum[1] << endl;
                if (sum[0] > sum[1]) {
                    return true;
                }
                return false;
            }

            if (left > right) {
                cout << "finish " << sum[0] << ":" << sum[1] << endl;
                if (sum[0] > sum[1]) {
                    return true;
                }
                return false;
            }

            // left left
            left    = left_backup;
            right   = right_backup;
            sum[0]  = sum_backup[0];
            sum[1]  = sum_backup[1];

            sum[0] = nums[left++] + sum[0];
            sum[1] = nums[left++] + sum[1];
            /**
            if (play(nums, sum) == false) {
                left    = left_backup;
                right   = right_backup;
                sum[0]  = sum_backup[0];
                sum[1]  = sum_backup[1];
                return false;
            }
            **/
            bool b1 = play(nums, sum);

            // left right
            left    = left_backup;
            right   = right_backup;
            sum[0]  = sum_backup[0];
            sum[1]  = sum_backup[1];

            sum[0] = nums[left++] + sum[0];
            sum[1] = nums[right--] + sum[1];
            /**
            if (play(nums, sum) == false) {
                left    = left_backup;
                right   = right_backup;
                sum[0]  = sum_backup[0];
                sum[1]  = sum_backup[1];
                return false;
            }
            **/
            bool b2 = play(nums, sum);



            // right left
            left    = left_backup;
            right   = right_backup;
            sum[0]  = sum_backup[0];
            sum[1]  = sum_backup[1];

            sum[0] = nums[right--] + sum[0];
            sum[1] = nums[left++] + sum[1];
            /**
            if (play(nums, sum) == false) {
                left    = left_backup;
                right   = right_backup;
                sum[0]  = sum_backup[0];
                sum[1]  = sum_backup[1];
                return false;
            }
            **/
            bool b3 = play(nums, sum);

            // right right
            left    = left_backup;
            right   = right_backup;
            sum[0]  = sum_backup[0];
            sum[1]  = sum_backup[1];

            sum[0] = nums[right--] + sum[0];
            sum[1] = nums[right--] + sum[1];
            /**
            if (play(nums, sum) == false) {
                left    = left_backup;
                right   = right_backup;
                sum[0]  = sum_backup[0];
                sum[1]  = sum_backup[1];
                return false;
            }
            **/
            bool b4 = play(nums, sum);

            if (b1 || b2 || b3 || b4) {
                return true;
            }

            return false;

        }

};

int main() {
    Solution * o = new Solution();
    {
        vector<int> nums = {1, 5, 2};
        cout << o->PredictTheWinner(nums) << endl;
    }
    {
        vector<int> nums = {1, 5, 233, 7};
        cout << o->PredictTheWinner(nums) << endl;
    }
    return 0;
}
