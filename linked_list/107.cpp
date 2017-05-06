#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode* removeElements(ListNode* head, int val) {
            ListNode dummy(0);
            dummy.next = head;

            ListNode * p = &dummy;
            while(p->next) {
                if (p->next->val == val) {
                    p->next = p->next->next;
                } else {
                    p= p->next;
                }
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
    ListNode a(1);
    ListNode b(2);
    ListNode c(6);
    ListNode d(3);
    ListNode e(4);
    ListNode f(5);
    ListNode g(6);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;
    d.next  = &e;
    e.next  = &f;
    f.next  = &g;
    g.next  = NULL;


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);


    cout << "delete " << endl;
    ListNode * tmp = o.removeElements(&a, 6);
    o.printList(tmp);


    ListNode aa(6);
    aa.next = NULL;
    cout << "delete " << endl;
    tmp = o.removeElements(&aa, 6);
    o.printList(tmp);

    ListNode aaa(6);
    ListNode bbb(7);
    aaa.next    = &bbb;
    bbb.next    = NULL;
    cout << "delete " << endl;
    tmp = o.removeElements(&aaa, 6);
    o.printList(tmp);

    ListNode aaaa(6);
    ListNode bbbb(6);
    aaaa.next   = &bbbb;
    cout << "delete " << endl;
    tmp = o.removeElements(&aaaa, 6);
    o.printList(tmp);

    cout << "delete NULL" << endl;
    tmp = o.removeElements(NULL, 6);
    o.printList(tmp);

    return 0;
}
