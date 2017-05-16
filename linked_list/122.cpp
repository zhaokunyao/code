#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            ListNode * dummy    = new ListNode(0);
            ListNode * p_fast   = head;
            dummy->next         = head;
            ListNode * p_slow   = dummy;

            int i = 0;
            for (i = 0; i < n; i++) {
                p_fast  = p_fast->next;
            }

            while(p_fast) {
                p_fast  = p_fast->next;
                p_slow  = p_slow->next;
            }
            // cout << p_slow->val << endl;
            if (p_slow->next) {
                p_slow->next    = p_slow->next->next;
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
    ListNode d(4);
    ListNode e(5);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;
    d.next  = &e;


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);

    cout << "removeNthFromEnd" << endl;
    ListNode * tmp = o.removeNthFromEnd(&a, 2);
    o.printList(tmp);

    ListNode aa(1);
    cout << "original list:" << endl;
    o.printList(&aa);

    cout << "removeNthFromEnd" << endl;
    ListNode * tmp2 = o.removeNthFromEnd(&aa, 1);
    o.printList(tmp2);

    return 0;
}
