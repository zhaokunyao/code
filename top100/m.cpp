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
        TreeNode * sortedArrayToBST(vector<int> &nums) {
            return sortedArrayToBST2(nums, 0, nums.size());
        }

        TreeNode* sortedArrayToBST2(vector<int>& nums, int low, int high) {
            if (high <= low) return NULL;
            int mid = (low+high)/2;
            TreeNode * root = new TreeNode(nums[mid]);
            root->left =  sortedArrayToBST2(nums, low, mid);
            root->right = sortedArrayToBST2(nums, mid+1, high);
            return root;
        }

        vector<int> inOrderTraversal(TreeNode * root) {
            vector<int> res;
            TreeNode * p = root;
            stack <TreeNode *> sk;
            while(true) {
                if (not p && sk.empty()) {
                    break;
                }
                if (p) {
                    // cout << "pushing " << p->val << endl;
                    sk.push(p);
                    p=p->left;
                } else {
                    TreeNode * tmp = sk.top();
                    // cout << "popping " << tmp->val << endl;
                    sk.pop();
                    res.push_back(tmp->val);
                    p = tmp->right;
                }
            }
            return res;
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
