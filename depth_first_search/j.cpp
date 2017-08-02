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
    bool isValidBST(TreeNode* root) {
        if (!root) {
            return true;
        }
        if (root->left) {
            int m_l = max(root->left);
            if (m_l >= root->val) {
                return false;
            }
        }
        if (root->right) {
            int m_r = min(root->right);
            if (m_r <= root->val) {
                return false;
            }
        }
        return isValidBST(root->left) && isValidBST(root->right);
    }

    int max(TreeNode * root) {
        int m = root->val;
        if (root->left) {
            int t = max(root->left);
            if (t > m) {
                m = t;
            }
        }
        if (root->right) {
            int t = max(root->right);
            if (t > m) {
                m = t;
            }
        }
        return m;
    }

    int min(TreeNode * root) {
        int m = root->val;
        if (root->left) {
            int t = min(root->left);
            if (t < m) {
                m = t;
            }
        }
        if (root->right) {
            int t = min(root->right);
            if (t < m) {
                m = t;
            }
        }
        return m;
    }
};

int main() {
    Solution o;

    {
        TreeNode * root = new TreeNode(2);
        root->left = new TreeNode(1);
        root->right = new TreeNode(3);
        cout << o.isValidBST(root) << endl;
    }
    {
        TreeNode * root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        cout << o.isValidBST(root) << endl;
    }

    return 0;
}

