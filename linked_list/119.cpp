#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head) {
            ListNode *dummy = new ListNode(0);
            dummy->next     = head;
            bool is_in           = false;
            ListNode * p    = dummy;
            while(p->next && p->next->next) {
                if (p->next->val == p->next->next->val) {
                    p->next = p->next->next;
                    is_in   = true;
                } else {
                    if (is_in) {
                        p->next = p->next->next;
                    } else {
                        p   = p->next;
                    }
                    is_in   = false;
                }
                // printList(dummy->next);
                // cout << p->val << endl;
            }
            if (is_in) {
                p->next = NULL;
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
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(3);
    ListNode e(4);
    ListNode f(4);
    ListNode g(4);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;
    d.next  = &e;
    e.next  = &f;
    f.next  = &g;


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);

    cout << "deleteDuplicates" << endl;
    ListNode * tmp = o.deleteDuplicates(&a);
    o.printList(tmp);

    return 0;
}
