#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

class Solution {
    public:
        vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
            vector<int> r;
            stack<int> s;
            map<int, int> m;

            // 把stack里面小于n的值都pop出来
            // 则被pop出来的值的 next great value就是n
            // stack为[1], n=3, 需要pop 1, 那么1的next great value就是3，然后push n
            // stack为[3]，n=4, 需要pop 3, 那么3的next great value就是4，然后push n
            // stack为[4]，n=2，不需要pop， 无法判断2的next great value. push n即可
            // stack为[4,2]，n=5，需要pop 2和4， 那么2与4的next great value都是5. 
            for (auto n : nums) {
                while (true) {
                    if (s.empty()) {
                        break;
                    }

                    int top = s.top();
                    if (n < top) {
                        break;
                    }

                    m[top] = n;
                    s.pop();    // return void ..
                }

                cout << "pushing " << n << endl;
                s.push(n);
            }

            for (auto k : m) {
                cout << k.first << ":" << k.second << endl;
            }

            for (auto n : findNums) {
                int ngv = -1;
                if (m.count(n) > 0) {
                    ngv = m[n];
                }
                r.push_back(ngv);
            }

            return r;
        }
};

int main(){
    Solution * o = new Solution();

    {
        vector<int> findNums = {4,1,2};
        vector<int> nums = {1,3,4,2};
        vector<int> r   = o->nextGreaterElement(findNums, nums);
        for (auto n : r) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
