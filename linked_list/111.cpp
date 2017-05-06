#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:

        ListNode* rotateRight(ListNode* head, int k) {
            int len = 1;
            ListNode * p = head;
            if (!p) {
                return p;
            }
            while(p->next) {
                p = p->next;
                len++;
            }
            // make a cycle.
            p->next = head;

            p   = head;
            k = k % len;

            for(int i = 0; i< len-k-1; i++) {
                p = p->next;
            }
            ListNode * ret = p->next;
            p->next = NULL;
            return ret;
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


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);

    cout << "rotate:" << endl;
    ListNode * tmp = o.rotateRight(&a, 2);
    // ListNode * tmp = o.rotateRight(&a, 7);
    o.printList(tmp);

    return 0;
}
