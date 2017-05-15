#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        // can also use two lists like in 121.cpp
        ListNode* partition(ListNode* head, int x) {
            if (!head || !head->next) {
                return head;
            }

            ListNode * dummpy = new ListNode(0);
            dummpy->next    = head;

            ListNode * p    = dummpy;
            ListNode * p2   = dummpy;

            while(true) {
                // find the last node which less than x.
                while(p->next && p->next->val < x) {
                    p   = p->next;
                }
                if (!p->next) {
                    cout << "breaked" << endl;
                    break;
                }

                p2  = p;
                // find the last next node which more than x
                while(p2 && p2->next && p2->next->val >= x) {
                    p2  = p2->next;
                }

                // p2 reach the end.
                if (!p2 || !p2->next) {
                    break;
                }

                // insert p2->next 
                ListNode * tmp  = p->next;
                ListNode * tmp2 = p2->next->next;
                p->next     = p2->next;
                p->next->next   = tmp;
                p2->next    = tmp2;
            }

            return dummpy->next;
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
    ListNode b(4);
    ListNode c(3);
    ListNode d(2);
    ListNode e(5);
    ListNode f(2);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;
    d.next  = &e;
    e.next  = &f;


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);

    cout << "partition" << endl;
    ListNode * tmp = o.partition(&a, 3);
    o.printList(tmp);

    return 0;
}
