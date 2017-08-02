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
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int m_l = minDepth(root->left);
        int m_r = minDepth(root->right);

        if (m_l == 0 && m_r != 0) {
            return m_r + 1;
        }

        if (m_r == 0 && m_l != 0) {
            return m_l + 1;
        }

        return min(m_l, m_r) + 1;
    }
};

int main() {
    Solution o;

    {
        TreeNode * root = new TreeNode(0);
        root->left = new TreeNode(1);
        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);

        cout << o.minDepth(root) << endl;
    }

    return 0;
}
