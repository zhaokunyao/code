#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        void deleteNode(ListNode* node) {
            ListNode * p = node->next;
            node->val = p->val;
            node->next  = p->next;
        }
};

int main() {
    Solution o;
    {
        ListNode * a = new ListNode(1);
        ListNode * b = new ListNode(2);
        ListNode * c = new ListNode(3);
        ListNode * d = new ListNode(4);
        a->next = b;
        b->next = c;
        c->next = d;
        o.deleteNode(b);

        cout << a->next->val << endl;
        cout << a->next->next->val << endl;
    }
    return 0;
}

