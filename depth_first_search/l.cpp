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
    int rob(TreeNode* root) {
        int o = r_odd(root, 0);
        int e = r_odd(root, 1);
        // cout << "o :" << o << " e: " << e << endl;
        return max(o, e);
    }

    int r_odd(TreeNode * root, int is_rub) {
        if (!root) {
            return 0;
        }
        int s = 0;
        if (is_rub) {
            s += root->val;
            s += r_odd(root->left, 0);
            s += r_odd(root->right, 0);
        } else {
            s = 0;
            int a = r_odd(root->left, 0);
            int b = r_odd(root->left, 1);
            int c = r_odd(root->right, 0);
            int d = r_odd(root->right, 1);

            s += b;
            s += d;

            int s2  = 0;
            s2 += a;
            s2 += c;

            if (s2>s) s = s2;

            int s3 = 0;
            s3 += a;
            s3 += d;
            if (s3 > s) s = s3;

            int s4 = 0;
            s4 += b;
            s4 += c;
            if (s4 > s) s = s4;
        }


        return s;

    }

};

int main() {
    Solution o;
    {
        TreeNode * root = new TreeNode(4);
        root->left = new TreeNode(1);
        root->left->left = new TreeNode(2);
        root->left->left->left = new TreeNode(3);
        cout << o.rob(root) << endl;
    }

    {
        TreeNode * root = new TreeNode(3);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->right = new TreeNode(3);
        root->right->right = new TreeNode(1);
        cout << o.rob(root) << endl;
    }
    {
        TreeNode * root = new TreeNode(3);
        root->left = new TreeNode(4);
        root->right = new TreeNode(5);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(3);
        root->right->right = new TreeNode(1);
        cout << o.rob(root) << endl;
    }

    return 0;
}

