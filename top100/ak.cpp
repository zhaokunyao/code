#include <iostream>
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
        vector<vector<int>> levelOrder(TreeNode* root) {
            vector<vector<int>> res;
            queue<TreeNode*> q;
            if (!root) return res;
            q.push(root);
            while(not q.empty()) {
                vector<int> vec;
                queue<TreeNode*> qq;
                while(not q.empty()) {
                    TreeNode * tmp  = q.front();
                    if (tmp->left) {
                        qq.push(tmp->left);
                    }
                    if (tmp->right) {
                        qq.push(tmp->right);
                    }
                    q.pop();
                    vec.push_back(tmp->val);
                }
                res.push_back(vec);
                q = qq;
            }

            return res;
        }
};

int main() {
    Solution o;
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
        vector<vector<int>> res= o.levelOrder(root);
        for (auto && vec : res) {
            for (auto && n: vec) {
                cout << n << ",";
            }
            cout << endl;
        }
    }
    return 0;
}
