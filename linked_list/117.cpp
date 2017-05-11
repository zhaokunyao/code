#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:

        ListNode* reverseBetween(ListNode* head, int m, int n) {

            ListNode * p    = head;
            ListNode * old;
            ListNode * pm;

            for (int i = 0; i < m-1; i++) {
                old = p;
                p = p->next;
            }

            pm = old;

            for(int i = 0; i < n-m+1; i++) {
                ListNode * p2   = p->next;
                p->next = old;
                old     = p;
                p       = p2;
            }

            if (m == 1) {
                head->next  = p;
                return old;
            } else {
                pm->next->next  = p;
                pm->next    = old;
                return head;
            }
        }


        void printList(ListNode * head) {
            while (head) {
                cout << head->val << "->" ;
                head = head->next;
            }
            cout << "NULL" << endl;
        }

};

int main() {
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;
    d.next  = &e;


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);

    cout << "reverse:" << endl;
    ListNode * tmp = o.reverseBetween(&a, 2, 4);
    o.printList(tmp);

    return 0;
}
