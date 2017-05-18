#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:

        ListNode* swapPairs(ListNode* head) {
            ListNode * dummy = new ListNode(0);
            dummy->next     = head;
            ListNode * p    = dummy;

            // p->a->b->c->d->null
            while(p->next && p->next->next) {
                ListNode * a = p->next;
                ListNode * b = p->next->next;
                ListNode * c = p->next->next->next;
                p->next->next = c;  // a->c
                p->next = b;        // p->b
                p->next->next = a;  // b->a
                p   = p->next->next;
            }

            return dummy->next;
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
    {
        ListNode a(1);
        ListNode b(2);
        ListNode c(3);
        ListNode d(4);

        a.next  = &b;
        b.next  = &c;
        c.next  = &d;



        Solution o;
        cout << "original list:" << endl;
        o.printList(&a);

        cout << "swapPairs" << endl;
        ListNode * tmp = o.swapPairs(&a);
        o.printList(tmp);
    }
    {
        ListNode a(1);
        ListNode b(2);
        ListNode c(3);

        a.next  = &b;
        b.next  = &c;


        Solution o;
        cout << "original list:" << endl;
        o.printList(&a);

        cout << "swapPairs" << endl;
        ListNode * tmp = o.swapPairs(&a);
        o.printList(tmp);
    }

    return 0;
}
