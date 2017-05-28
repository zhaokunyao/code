#include <iostream>
#include <vector>
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
            vector<int> r ;
            stack<TreeNode *> s;
            TreeNode * p    = root;

            while(true) {
                if (s.empty() && not p) {
                    break;
                }
                if (p) {
                    cout << "push " << p->val << endl;
                    s.push(p);
                    p  = p->left;
                } else {
                    p = s.top();
                    s.pop();
                    cout << "pop " << p->val << endl;
                    r.push_back(p->val);
                    p = p->right;
                }

            }

            return r;
        }
};

int main() {
    Solution * o = new Solution();
    {
        TreeNode * root = new TreeNode(1);
        root->left      = NULL;
        root->right     = new TreeNode(2);
        root->right->left = new TreeNode(3);

        vector<int> r = o->inorderTraversal(root);
        for (auto n : r) {
            cout << n << ",";
        }
        cout << endl;
    }
}
