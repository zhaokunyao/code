#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode* oddEvenList(ListNode* head) {
            ListNode * odd  = new ListNode(0);
            ListNode * even = new ListNode(0);
            ListNode * p    = head;
            ListNode * po   = odd;
            ListNode * pe   = even;

            int i = 1;
            while(p) {
                if (i % 2 == 1) {
                    po->next   = p;
                    po  = po->next;
                } else {
                    pe->next = p;
                    pe  = pe->next;
                }
                i ++;
                p = p->next;
            }
            po->next    = NULL;
            pe->next    = NULL;
            printList(odd);
            printList(even);

            po->next    = even->next;
            return odd->next;
        }
        void printList(ListNode * head) {
            ListNode * p = head;
            while (p) {
                cout << p->val << "->" ;
                p   = p->next;
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

    cout << "odd even" << endl;
    ListNode * tmp = o.oddEvenList(&a);
    o.printList(tmp);

    return 0;
}
