#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            int carry   = 0;
            ListNode * dummy    = new ListNode(0);
            ListNode * p_sum    = dummy;

            while(l1 && l2) {
                int sum = l1->val + l2->val + carry;
                carry   = (int)sum / 10;
                sum = sum % 10;
                p_sum->next = new ListNode(sum);
                p_sum   = p_sum->next;
                l1      = l1->next;
                l2      = l2->next;
            }

            while(l1) {
                int sum = l1->val + carry;
                carry   = (int)sum / 10;
                sum = sum % 10;
                p_sum->next = new ListNode(sum);
                p_sum   = p_sum->next;
                l1  = l1->next;
            }
            while(l2) {
                int sum = l2->val + carry;
                carry   = (int)sum / 10;
                sum = sum % 10;
                p_sum->next = new ListNode(sum);
                p_sum   = p_sum->next;
                l2  = l2->next;
            }

            if ( carry) {
                p_sum->next = new ListNode(carry);
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
    ListNode a(2);
    ListNode b(4);
    ListNode c(3);

    a.next  = &b;
    b.next  = &c;

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
