/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (not root) return;
        root->next = NULL;
        if (root->left)
            c2(root->left, root);
        if (root->right)
            c2(root->right, root);
    }
    void c2(TreeLinkNode * root , TreeLinkNode * parent) {
        if (root != parent->right)
            root->next = parent->right;
        if (parent->next) {
            if (parent->next->left)
                root->next->next = parent->next->left;
            else
                root->next->next = parent->next->right;
        }
    

        if (root->left) {
            c2(root->left, root);
        }
        if (root->right) {
            c2(root->right, root);
        }
    }
};
