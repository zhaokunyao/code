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
        ListNode* reverseList(ListNode* head) {
            if (!head) {
                return head;
            }
            ListNode * p_old = NULL;
            ListNode * p = head;
            while(p) {
                ListNode * tmp = p->next;
                p->next = p_old;
                p_old = p;
                p = tmp;
            }
            return p_old;
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
        ListNode  * t  = o.reverseList(a);

        while(t) {
            cout << t->val << "," ;
            t = t->next;
        }
        cout << endl;
    }
    return 0;
}

