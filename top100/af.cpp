#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
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
        int kthSmallest(TreeNode* root, int k) {
            vector<int> res = inOrder(root);
            return res[k-1];
        }

        vector<int> inOrder(TreeNode * root) {
            TreeNode * p = root;
            stack<TreeNode *> sk;
            vector<int> res;

            while(true) {
                if (sk.empty() && not p) {
                    break;
                }
                if (p) {
                    sk.push(p);
                    p= p->left;
                } else {
                    TreeNode * tmp = sk.top();
                    sk.pop();
                    res.push_back(tmp->val);
                    p = tmp->right;
                }
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        TreeNode * root = new TreeNode(1);
        int k =1;
        cout << o.kthSmallest(root, k) << endl;
    }
    return 0;
}
