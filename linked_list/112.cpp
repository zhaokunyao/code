#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        // 103
        ListNode * middleNode(ListNode *head) {
            if (!head) {
                return NULL;
            }
            if (!head->next) {
                return head;
            }
            ListNode * a = head;
            ListNode * b = head;

            while(b->next && b->next->next) {
                a = a->next;
                b = b->next->next;
            }

            return a;

        }

        // 110
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

        ListNode* sortList(ListNode* head) {
            if (!head || !head->next) {
                // cout << "   return " << head->val << endl;
                return head;
            }

            // 3 2 4
            ListNode * p2   = middleNode(head);
            // cout << "middle:" << p2->val <<endl;
            ListNode * p1   = head;
            ListNode * p3   = p2->next;

            p3 = sortList(p3);
            // cout << "after sort right:" << p2->val << endl;
            // printList(p3);

            p2->next     = NULL;

            p1 = sortList(p1);
            // cout << "after sort left:" << p2->val << endl;
            // printList(p1);

            // cout << "before merge :" << p2->val << endl;
            // printList(p1);
            // printList(p3);
            ListNode * ret = mergeTwoLists(p1, p3);
            // cout << "after merge :" << p2->val << endl;
            // printList(ret);
            return ret;
        }

        void printList(ListNode * head) {
            ListNode * p = head;
            while (p) {
                cout << p->val << "->" ;
                p = p->next;
            }
            cout << "NULL" << endl;
        }

};

int main() {
    Solution o;

/**
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
    ListNode * tmp = o.sortList(&a);
    o.printList(tmp);
    **/

    ListNode aa(3);
    ListNode bb(2);
    ListNode cc(4);
    aa.next = &bb;
    bb.next = &cc;

    cout << "original list:" << endl;
    o.printList(&aa);

    cout << "sort:" << endl;
    ListNode * tmp = o.sortList(&aa);
    o.printList(tmp);

    return 0;
}
