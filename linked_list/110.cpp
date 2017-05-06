#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
            ListNode dummy(0);
            ListNode * head = & dummy;

            while(l1 && l2) {
                if (l1->val < l2->val) {
                    head->next = l1;
                    l1  = l1->next;
                } else {
                    head->next = l2;
                    l2  = l2->next;
                }
                head = head->next;
            }
            if (l1) {
                head->next   = l1;
            }
            if (l2) {
                head->next   = l2;
            }
            return dummy.next;
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
    ListNode a(11);
    ListNode b(22);
    ListNode c(33);
    ListNode d(44);
    ListNode e(55);
    ListNode f(66);
    ListNode g(77);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;
    d.next  = &e;
    e.next  = &f;
    f.next  = &g;
    g.next  = NULL;


    ListNode aa(7);
    ListNode bb(10);
    ListNode cc(15);
    ListNode dd(60);
    ListNode ee(100);
    aa.next = &bb;
    bb.next = &cc;
    cc.next = &dd;
    dd.next = &ee;


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);
    o.printList(&aa);

    cout << "merge:" << endl;
    ListNode * tmp = o.mergeTwoLists(&a, &aa);
    o.printList(tmp);

    return 0;
}
