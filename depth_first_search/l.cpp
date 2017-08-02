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
        return max(r_odd(root, 1), r_even(root, 1));
    }

    int r_odd(TreeNode * root, int level) {
        if (!root) {
            return 0;
        }
        int s = 0;
        if (level % 2 == 1) {
            s += root->val;
        }
        level ++;
        return  s + r_odd(root->left, level) + r_odd(root->right, level);
    }

    int r_even(TreeNode * root, int level) {
        if (!root) {
            return 0;
        }
        int s = 0;
        if (level % 2 == 0) {
            s += root->val;
        }
        level ++;
        return s + r_even(root->left, level) + r_even(root->right, level);
    }
};

int main() {
    Solution o;

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

