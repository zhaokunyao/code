#include <iostream>
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
        vector<string> binaryTreePaths(TreeNode* root) {
            vector<string> vec;
            if (!root) {
                return vec;
            }
            vector<string> vec_left;
            vector<string> vec_right;
            if (root->left) {
                vec_left = binaryTreePaths(root->left);
            }
            if (root->right) {
                vec_right = binaryTreePaths(root->right);
            }
            if (!root->left && !root->right) {
                string str = to_string(root->val);
                vec.push_back(str);
                return vec;
            }
            for (auto && n : vec_left) {
                string str = to_string(root->val) + "->" + n;
                vec.push_back(str);
            }
            for (auto && n : vec_right) {
                string str = to_string(root->val) + "->" + n;
                vec.push_back(str);
            }
            return vec;
        }
};

int main() {
    Solution o;

    {
        TreeNode * root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->right = new TreeNode(5);
        vector<string> vec;
        vec = o.binaryTreePaths(root);
        for (auto && n: vec) {
            cout << n << ",";
        }
        cout << endl;
    }

    return 0;
}
