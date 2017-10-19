#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <queue>
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
        map<int, bool> used;
        vector<int> res_dfs;
        stack<int> stk;

        bool hasCycle(vector<pair<int, int>> prerequisites) {
        }

        vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
            vector<int> res;
            if (hasCycle(prerequisites)) {
                return res;
            }

            stk = stack<int>();
            used.clear();
            for (int i=0; i<numCourses; i++) {
                used[i] = false;
            }

            for (int i=0; i<numCourses; i++) {
                if (used[i]) {
                    continue;
                }

                tpSort(i, prerequisites);
            }

            while (!stk.empty()) {
                res.push_back(stk.top());
                stk.pop();
            }

            return res;
        }

        void tpSort(int v, vector<pair<int, int>> prerequisites) {
            used[v] = true;
            for (auto && pr : prerequisites) {
                int from = std::get<1>(pr);
                int to = std::get<0>(pr);
                if (from != v) {
                    continue;
                }
                if (used[to]) {
                    continue;
                }
                tpSort(to, prerequisites);
            }
            stk.push(v);
        }

        vector<int> findOrder2(int numCourses, vector<pair<int, int>>& prerequisites) {
            vector<int> res;
            map<int, bool> start_points;
            res_dfs.resize(0);
            for (int i =0; i<numCourses; i++) {
                start_points[i] = true;
                used[i] = false;
            }
            for (auto && pr : prerequisites) {
                start_points[get<0>(pr)] = false;
            }

            // 以各个入度为0的节点进行 bfs 遍历
            for (auto && p: start_points) {
                if (p.second) {
                    // dfs(prerequisites, p.first);
                    vector<int> tmp = bfs(prerequisites, p.first);
                    for (auto && n : tmp) {
                        res.push_back(n);
                    }
                }
            }

            return res;
        }

        void dfs(vector<pair<int, int>>& prerequisites, int point) {
            cout << " got " << point << endl;
            if (!used[point]) {
                used[point] = true;
                res_dfs.push_back(point);
            }
            for (auto && pr : prerequisites) {
                int from = get<1>(pr);
                int to = get<0>(pr);
                if (from !=point) {
                    continue;
                }
                // cout << from << ":" << to << endl;
                dfs(prerequisites, to);
            }
        }

        vector<int> bfs(vector<pair<int, int>>& prerequisites, int point) {
            queue<int> q;
            vector<int> res_bfs;
            if (!used[point]) {
                used[point] = true;
                q.push(point);
            }

            while(!q.empty()) {
                int point = q.front();
                q.pop();
                res_bfs.push_back(point);
                for (auto && pr : prerequisites) {
                    int from = get<1>(pr);
                    int to  = get<0>(pr);
                    if (from != point) {
                        continue;
                    }
                    if (used[to]) {
                        continue;
                    }
                    q.push(to);
                    used[to] = true;
                }
            }
            return res_bfs;
        }


};

int main() {
    Solution o;
    {
        int numCourses = 3;
        vector<pair<int, int>> prerequisites = {{1,0},{0,2},{2,1}};
        vector<int> res = o.findOrder(numCourses, prerequisites);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;
    }
    {
        int numCourses = 3;
        vector<pair<int, int>> prerequisites = {{0,2},{1,2},{2,0}};
        vector<int> res = o.findOrder(numCourses, prerequisites);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;
    }

    {
        int numCourses = 2;
        vector<pair<int, int>> prerequisites = {{0, 1}, {1, 0}};
        vector<int> res = o.findOrder(numCourses, prerequisites);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;
    }

    {
        int numCourses = 3;
        vector<pair<int, int>> prerequisites = {{2, 0}, {2, 1}};
        vector<int> res = o.findOrder(numCourses, prerequisites);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;
    }

    {
        int numCourses = 2;
        vector<pair<int, int>> prerequisites = {};
        vector<int> res = o.findOrder(numCourses, prerequisites);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;
    }

    {
        int numCourses = 4;
        vector<pair<int, int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
        vector<int> res = o.findOrder(numCourses, prerequisites);
        for (auto && n : res) {
            cout << n << ",";
        }
        cout << endl;
    }

    return 0;
}

