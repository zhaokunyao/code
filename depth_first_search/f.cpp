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
    bool isBalanced(TreeNode* root) {
        if (!root) {
            return true;
        }
        int height_left = height(root->left);
        int height_right = height(root->right);
        if (abs(height_left-height_right) > 1) {
            return false;
        }
        return isBalanced(root->left) && isBalanced(root->right);
    }

    int height(TreeNode * root) {
        if (!root) {
            return 0;
        }

        int h_l = height(root->left);
        int h_r = height(root->right);
        return max(h_l, h_r) + 1;
    }
};

int main() {
    Solution o;

    {
        TreeNode * root = new TreeNode(0);
        root->left = new TreeNode(1);
        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);

        cout << o.isBalanced(root) << endl;
    }

    return 0;
}
