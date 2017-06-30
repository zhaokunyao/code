#include <iostream>
#include <algorithm>
#include <limits.h>
#include <map>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
            queue<TreeNode *> q;
            vector<vector<int>> res;
            if (not root) {
                return res;
            }
            q.push(root);
            int loop = 0;
            while(not q.empty()) {
                vector<int> vec;
                queue<TreeNode *> q2;
                while(not q.empty()) {
                    TreeNode * p = q.front();
                    q.pop();
                    vec.push_back(p->val);
                    if (p->left) q2.push(p->left);
                    if (p->right) q2.push(p->right);
                }
                q = q2;
                loop ++;
                if (loop % 2 == 0) {
                    std::reverse(vec.begin(), vec.end());
                }
                res.push_back(vec);
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        TreeNode * root = new TreeNode(1);
        TreeNode * node ;
        node = new TreeNode(2);
        root->left = node;
        node = new TreeNode(3);
        root->right = node;
        node = new TreeNode(4);
        root->left->left = node;
        node = new TreeNode(5);
        root->right->right = node;
        vector<vector<int>> res= o.zigzagLevelOrder(root);
        for (auto && vec : res) {
            for (auto && n: vec) {
                cout << n << ",";
            }
            cout << endl;
        }
    }
    {
        TreeNode * root = new TreeNode(3);
        TreeNode * node ;
        node = new TreeNode(9);
        root->left = node;
        node = new TreeNode(20);
        root->right = node;
        node = new TreeNode(15);
        root->right->left = node;
        node = new TreeNode(7);
        root->right->right = node;
        vector<vector<int>> res= o.zigzagLevelOrder(root);
        for (auto && vec : res) {
            for (auto && n: vec) {
                cout << n << ",";
            }
            cout << endl;
        }
    }
    return 0;
}
