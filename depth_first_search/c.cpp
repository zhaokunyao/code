#include <iostream>
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
            return sortedArrayToBST2(nums, 0, nums.size()-1);
        }

        TreeNode * sortedArrayToBST2(vector<int> nums, int low, int high) {
            if (low > high) {
                return NULL;
            }
            int mid = (low + high) / 2;
            TreeNode * p = new TreeNode(nums[mid]);
            p->left = sortedArrayToBST2(nums, low, mid-1);
            p->right = sortedArrayToBST2(nums, mid+1, high);

            return p;
        }

        vector<int> inOrderTraversal(TreeNode * root) {
            stack<TreeNode *> sk;
            vector<int> vec;
            TreeNode * p = root;
            while(true) {
                if (sk.empty() && !p) {
                    break;
                }

                if (p) {
                    sk.push(p);
                    p = p->left;
                } else {
                    TreeNode * tmp = sk.top();
                    vec.push_back(tmp->val);
                    sk.pop();
                    p = tmp->right;
                }
            }

            return vec;
        }
};

int main() {
    Solution o;
    {
        vector<int> nums = {1,2,3,4,5,6};

        vector<int> r = o.inOrderTraversal(o.sortedArrayToBST(nums));
        for (auto && n : r) {
            cout << n << ",";
        }
        cout << endl;
    }

    return 0;
}
