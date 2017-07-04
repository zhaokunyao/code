#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
    map<TreeNode *, int> hash;
    vector<int> findFrequentTreeSum(TreeNode* root) {
        hash.clear();
        getSum(root);
        map<int, int> hash_count;
        int len = hash.size();
        for (auto && pair : hash) {
            hash_count[pair.second] ++;
        }
        vector<vector<int>> bucket(len+1);
        for (auto && pair : hash_count) {
            bucket[pair.second].push_back(pair.first);
        }

        vector<int> res;
        for (int i = bucket.size()-1; i > 0; i--){
            if (bucket[i].size() > 0) {
                res = bucket[i];
                break;
            }
        }

        return res;
    }

    int getSum(TreeNode * root) {
        int sum = 0;
        if (hash.count(root) > 0) {
            return hash[root];
        }
        if (!root) return sum;
        sum += root->val;
        if (root->left) sum += getSum(root->left);
        if (root->right) sum += getSum(root->right);
        hash[root] = sum;
        return sum;
    }
};

int main() {
    Solution o;
    {
        TreeNode * root = new TreeNode(5);
        root->left      = new TreeNode(2);
        root->right     = new TreeNode(-5);

        vector<int> r = o.findFrequentTreeSum(root);
        for (auto n : r) {
            cout << n << ",";
        }
        cout << endl;
    }
    return 0;
}
