#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        /**
         * addTwoNumbers
         *
         * 反转 反转 再反转
         * 如果不允许反转列表......把列表里面的node搞到stack里面，再从stack里面pop出来...
         * 也就变相地实现了反转
         *
         */
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            ListNode * p1   = reverseList(l1);
            ListNode * p2   = reverseList(l2);

            cout << "reverse" << endl;
            printList(p1);
            printList(p2);

            ListNode *dummy    = new ListNode(0);
            ListNode *p = dummy;

            int carry = 0;
            while(true) {
                if ( !p1 && !p2) {
                    break;
                }
                int sum = carry;
                if (p1) {
                    sum += p1->val;
                    p1 = p1->next;
                }
                if (p2) {
                    sum += p2->val;
                    p2 = p2->next;
                }
                if (sum >=10) {
                    sum     = sum - 10;
                    carry   = 1;
                } else {
                    carry   = 0;
                }
                p->next = new ListNode(sum);
                p = p->next;

            }
            if (carry == 1) {
                p->next = new ListNode(carry);
            }
            printList(dummy->next);

            return reverseList(dummy->next);
        }
        void printList(ListNode * head) {
            ListNode * p = head;
            while (p) {
                cout << p->val << "->" ;
                p   = p->next;
            }
            cout << "NULL" << endl;
        }

        // 108
        ListNode* reverseList(ListNode* head) {
            if (!head) {
                return NULL;
            }
            ListNode * p = head->next;
            ListNode * p2 = head;
            while (p) {
                ListNode * tmp = p->next;
                p->next = p2;
                p2 = p;
                p = tmp;
            }
            head->next = NULL;
            return p2;
        }


};

int main() {
    ListNode a(7);
    ListNode b(2);
    ListNode c(4);
    ListNode d(3);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;

    ListNode * aa   = new ListNode(5);
    ListNode * bb   = new ListNode(6);
    ListNode * cc   = new ListNode(4);
    aa->next    = bb;
    bb->next    = cc;


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);
    o.printList(aa);

    cout << "addTwoNumbers" << endl;
    ListNode * tmp = o.addTwoNumbers(&a, aa);
    o.printList(tmp);

    return 0;
}
