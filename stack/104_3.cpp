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
        vector<int> postorderTraversal(TreeNode* root) {
            vector<int> r ;
            stack<TreeNode *> s;
            TreeNode * p    = root;
            TreeNode * pold = NULL;

            while(true) {
                if (s.empty() && not p) {
                    break;
                }
                if (p) {
                    cout << "push " << p->val << endl;
                    s.push(p);
                    p  = p->left;
                } else {
                    TreeNode * ptmp = s.top();
                    // 没有右子树
                    if (!ptmp->right) {
                        r.push_back(ptmp->val);
                        s.pop();
                        cout << "pop " << ptmp->val << endl;
                        pold    = ptmp;
                        continue;
                    }
                    // 有右子树，但是上次pop出来的就是右子树
                    if (pold == ptmp->right) {
                        r.push_back(ptmp->val);
                        s.pop();
                        cout << "pop " << ptmp->val << endl;
                        pold    = ptmp;
                        continue;
                    }

                    // 不pop，直接遍历右子树
                    p = ptmp->right;
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
        root->right->right  = new TreeNode(4);

        vector<int> r = o->postorderTraversal(root);
        for (auto n : r) {
            cout << n << ",";
        }
        cout << endl;
    }
    {
        TreeNode * root = NULL;
        vector<int> r = o->postorderTraversal(root);
        for (auto n : r) {
            cout << n << ",";
        }
        cout << endl;
    }
}
