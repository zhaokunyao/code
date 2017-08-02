#include <iostream>
using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution { 
public: 
    void connect(TreeLinkNode *root) {
        if (!root) {
            return;
        }
        c2(root->left, root);
        c2(root->right, root);

        return;
    }

    void c2(TreeLinkNode *root, TreeLinkNode *parent) {
        if (!root) {
            return;
        }
        if (root == parent->left) {
            root->next = parent->right;
        } else {
            if (parent->next) {
                if (parent->next->left) {
                    root->next = parent->next->left;
                } else {
                    root->next = parent->next->right;
                }
            }
        }
        c2(root->left, root);
        c2(root->right, root);
    }
};

int main() {
    Solution o;

    {
        TreeLinkNode * root = new TreeLinkNode(0);
        root->left = new TreeLinkNode(1);
        root->right = new TreeLinkNode(2);
        root->right->right = new TreeLinkNode(3);

    }

    return 0;
}
