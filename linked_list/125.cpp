#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:

        ListNode* reverseKGroup(ListNode* head, int k) {
            if (!head || !head->next) {
                return head;
            }
            ListNode * dummy    = new ListNode(0);
            dummy->next         = head;

            ListNode * p        = head;
            ListNode * p2       = NULL;
            ListNode * tail     = NULL;
            // 

            // reverse k nodes
            // 1(p)->2->3->4->5
            int loop   = 1;
            ListNode * phead=NULL, *phead2=NULL;
            while (p) {
                ListNode * p3   = p;
                int l3          = 0;
                while(p3) {
                    p3  = p3->next;
                    l3++;
                    if (l3 >= k) {
                        break;
                    }
                }

                if (l3 < k) {
                    if (loop == 1) {
                        return head;
                    }
                    if (loop % 2== 1) {
                        phead2->next    = p;
                    } else {
                        phead->next  = p;
                    }
                    break;
                }

                if (loop % 2 == 1) {
                    phead  = p;
                } else {
                    phead2   = p;
                }
                for (int i =0; i< k; i++) {
                    ListNode * tmp  = p->next;
                    p->next = p2;        // 1->null
                    p2  = p;             // p2=1
                    p   = tmp;           // p=2
                }
                if (loop ==1) {
                    tail = p2;
                }

                // cout << "p: " << p->val << " p2: " << p2->val << endl;
                if (loop  % 2 == 1) {
                    if (phead2) {
                        phead2->next = p2;
                    }
                } else {
                    phead->next= p2;
                    cout <<  "making " << phead->val<< "'s next to: " << p2->val << endl;
                }
                // printList(tail);
                p2 = NULL;
                loop ++;
            }

            return tail;
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
        ListNode e(5);

        a.next  = &b;
        b.next  = &c;
        c.next  = &d;
        d.next  = &e;

        Solution o;
        cout << "original list:" << endl;
        o.printList(&a);

        cout << "Reverse" << endl;
        ListNode * tmp = o.reverseKGroup(&a, 2);
        o.printList(tmp);
    }

    {
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

        cout << "Reverse" << endl;
        ListNode * tmp = o.reverseKGroup(&a, 3);
        o.printList(tmp);
    }

    return 0;
}
