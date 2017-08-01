#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // not ok.
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {

            // cout << " q size " << q.size() << endl;
            vector<int> nums = {};
            queue<TreeNode*> q2;

            while (!q.empty()) {
                TreeNode * p = q.front();
                nums.push_back(p->val);
                q.pop();
                TreeNode * np = new TreeNode(INT_MAX);
                if (!p->left && !p->right) {
                    continue;
                }
                if (p->left) {
                    q2.push(p->left);
                } else {
                    q2.push(np);
                }
                if (p->right) {
                    q2.push(p->right);
                } else {
                    q2.push(np);
                }
            }

            q = q2;
            for (auto && n : nums) {
                cout << n << ",";
            }
            cout << endl;

            int len = nums.size();
            for (int i =0; i < len/2; i++) {
                int low = i;
                int high = len - i - 1;
                if (nums[low] != nums[high]) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution o;
    {
        TreeNode * root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(2);
        root->left->right = new TreeNode(3);
        root->right->right = new TreeNode(3);
        cout << o.isSymmetric(root) << endl;
    }

    {
        TreeNode * root = new TreeNode(1);
        root->left  = new TreeNode(2);
        root->right = new TreeNode(2);
        root->left->left = new TreeNode(3);
        root->left->right = new TreeNode(4);
        root->right->left = new TreeNode(4);
        root->right->right = new TreeNode(3);
        cout << o.isSymmetric(root) << endl;
    }

    return 0;
}
