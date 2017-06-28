#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
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
    bool isSymmetric(TreeNode* root) {
    }

};

int main() {
    Solution o;
    {
        vector<int> nums = {0,1,2,3,4,5};
        TreeNode * root = o.sortedArrayToBST(nums);
        cout << "======================" << endl;
        vector<int> res = o.inOrderTraversal(root);
        for (auto && n: res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    {
        vector<int> nums = {1,2,3,4,5};
        TreeNode * root = o.sortedArrayToBST(nums);
        cout << "======================" << endl;
        vector<int> res = o.inOrderTraversal(root);
        for (auto && n: res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    return 0;
}
