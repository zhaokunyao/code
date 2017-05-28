#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class Solution {
    public:
        vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
            vector<int> res;
            queue<int> q;
            // 用map的话，会快一些
            map<int, vector<int>> m;
            int i = 0;
            for (auto n : ppid) {
                m[n].push_back(pid[i]);
                i++;
            }
            while(true) {
                res.push_back(kill);
                for (auto ni : m[kill]) {
                    q.push(ni);
                }
                if (q.empty()) {
                    break;
                }
                kill = q.front();
                q.pop();
            }

            return res;

        }
};

int main() {
    Solution * o = new Solution();
    {
        vector<int> pid =   {1,3,10,5};
        vector<int> ppid =  {3,0,5,3};

        vector<int> pids    = o->killProcess(pid, ppid, 5);
        for (auto n : pids) {
            cout << n << ",";
        }
        cout << endl;
    }
    {
        vector<int> pid =   {1,3,10,4};
        vector<int> ppid =  {3,10,5,3};

        vector<int> pids    = o->killProcess(pid, ppid, 5);
        for (auto n : pids) {
            cout << n << ",";
        }
        cout << endl;
    }
}
