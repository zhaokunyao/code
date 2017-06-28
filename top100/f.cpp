#include <iostream>
#include <limits.h>
#include <map>
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
        int maxDepth(TreeNode* root) {
            if (!root) {
                return 0;
            }
            auto l = maxDepth(root->left);
            auto r = maxDepth(root->right);
            return std::max(l, r) + 1;

        }
};

int main() {
    Solution o;
    {
        TreeNode * root = new TreeNode(0);
        root->left = new TreeNode(1);
        root->left->left = new TreeNode(2);
        cout << o.maxDepth(root) << endl;
    }
    return 0;
}
