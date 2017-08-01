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
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int ml = maxDepth(root->left);
        int mr = maxDepth(root->right);
        return max(ml, mr) + 1;
    }
};

int main() {
    Solution o;

    {
        TreeNode * root = new TreeNode(0);
        root->left = new TreeNode(1);
        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);

        cout << o.maxDepth(root) << endl;
    }

    return 0;
}
