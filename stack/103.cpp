#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
using namespace std;

class Solution {
    public:
        // 103_0
        vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
            vector<int> r;
            stack<int> s;
            map<int, int> m;

            int i = 0;
            for (auto n : nums) {
                while (true) {
                    if (s.empty()) {
                        break;
                    }

                    int top = s.top();
                    if (n <= nums[top]) {
                        break;
                    }

                    m[top] = n;
                    s.pop();    // return void ..
                }

                s.push(i);
                i ++;
            }


            int j = 0;
            for (auto n : findNums) {
                int ngv = -1;
                if (m.count(j) > 0) {
                    ngv = m[j];
                }
                r.push_back(ngv);
                j++;
            }

            return r;
        }

        vector<int> nextGreaterElements(vector<int>& nums) {
            vector<int> nums2;
            for (auto n : nums) {
                nums2.push_back(n);
            }
            for (auto n : nums) {
                nums2.push_back(n);
            }
            return nextGreaterElement(nums, nums2);
        }
};

int main(){
    Solution * o = new Solution();

    {
        vector<int> nums = {1,2,1};
        vector<int> r   = o->nextGreaterElements(nums);
        for (auto n : r) {
            cout << n << ",";
        }
        cout << endl;
    }

    return 0;
}
