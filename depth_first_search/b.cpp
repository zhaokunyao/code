#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        bool isSameTree(TreeNode* p, TreeNode* q) {
            if (p && !q) {
                return false;
            }
            if (!p && q) {
                return false;
            }
            if (!p && !q) {
                return true;
            }
            if (p->val != q->val) {
                return false;
            }
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
};

int main() {
    Solution o;

    {
        TreeNode * root = new TreeNode(0);
        root->left = new TreeNode(1);
        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);

        TreeNode * p = new TreeNode(0);
        p->left = new TreeNode(1);
        p->right = new TreeNode(2);
        p->right->right = new TreeNode(3);

        cout << o.isSameTree(root, p) << endl;
    }

    return 0;
}
