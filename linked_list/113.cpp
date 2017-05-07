#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:

        ListNode* insertionSortList(ListNode* head) {
            if (!head) {
                return head;
            }
            if (!head->next) {
                return head;
            }
            ListNode dummy(0);
            ListNode * p2   = &dummy;
            dummy.next      = head;

            ListNode * p    = head;


            // 3 4 1
            // 1 3 4
            while(p->next) {
                // cout << "P:" << p->val << endl;
                while (p2->next->val < p->next->val) {
                    p2 = p2->next;
                }
                if (p2  == p) {
                    p2  = &dummy;
                    p   = p->next;
                    continue;
                }
                ListNode * tmp2 = p2->next;

                p2->next        = p->next;
                p->next         = p->next->next;
                p2->next->next  = tmp2;

                p2  = &dummy;
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
    Solution o;

    ListNode a(11);
    ListNode b(22);
    ListNode c(44);
    ListNode d(33);
    ListNode e(55);
    ListNode f(166);
    ListNode g(77);

    a.next  = &b;
    b.next  = &c;

    c.next  = &d;
    d.next  = &e;
    e.next  = &f;
    f.next  = &g;
    g.next  = NULL;


    cout << "original list:" << endl;
    o.printList(&a);

    cout << "sort:" << endl;
    ListNode * tmp = o.insertionSortList(&a);
    o.printList(tmp);

    ListNode aa(3);
    ListNode bb(2);
    aa.next = &bb;

    cout << "original list:" << endl;
    o.printList(&aa);

    cout << "sort:" << endl;
    tmp = o.insertionSortList(&aa);
    o.printList(tmp);

    return 0;
}
