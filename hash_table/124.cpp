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
        vector<int> inorderTraversal(TreeNode* root) {
            stack<TreeNode *> sk;
            vector<int> res;
            TreeNode * p = root;

            while(true) {
                if (sk.empty() && !p) {
                    break;
                }

                if (p) {
                    sk.push(p);
                    p = p->left;
                } else {
                    TreeNode * x = sk.top();
                    res.push_back(x->val);
                    sk.pop();
                    p = x->right;
                }
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        TreeNode * root = new TreeNode(1);
        root->left      = NULL;
        root->right     = new TreeNode(2);
        root->right->left = new TreeNode(3);

        vector<int> r = o.inorderTraversal(root);
        for (auto n : r) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
