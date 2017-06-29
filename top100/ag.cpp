#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* oddEvenList(ListNode* head) {
            if (!head || !head->next) return head;
            ListNode * p1 = new ListNode(0);
            ListNode * p2 = new ListNode(0);
            ListNode * p2old = p2;

            ListNode * p = head;
            int i = 0;
            while(p) {
                if (i%2 ==0) {
                    p1->next = p;
                    p1 =p1->next;
                } else {
                    p2->next = p;
                    p2 = p2->next;
                }
                p= p->next;
                i++;
            }
            p2->next = NULL;
            p1->next =p2old->next;

            return head;

        }

        void printList(ListNode * p) {
            ListNode * tmp = p;
            while(tmp) {
                cout << tmp->val << "->" ;
                tmp = tmp->next;
            }
            cout << endl;
        }
};

int main() {
    Solution o;
    {
        ListNode * a = new ListNode(1);
        ListNode * b = new ListNode(2);
        ListNode * c = new ListNode(3);
        ListNode * d = new ListNode(4);
        ListNode * e = new ListNode(5);
        ListNode * f = new ListNode(6);
        ListNode * g = new ListNode(7);
        ListNode * h = new ListNode(8);
        a->next = b;
        b->next = c;
        c->next = d;
        d->next =e ; e->next =f ; f->next =g; g->next  = h;
        ListNode * tmp = o.oddEvenList(a);
        o.printList(tmp);
    }
    return 0;
}
